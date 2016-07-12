package main

import (
	"fmt"
	"github.com/sirpent-team/sirpent-go"
	"time"
)

func main() {
	// Configure all players.
	players := make(map[sirpent.UUID]*sirpent.Player)
	player_addresses := []string{"localhost:8901", "localhost:8902"}
	for i := range player_addresses {
		player := sirpent.NewPlayer(player_addresses[i])
		players[player.ID] = player
	}

	// Create game datastructures.
	grid := &sirpent.HexGridHexagonal{Rings: 20}
	game := sirpent.NewGame(grid, players)

	bs, _ := game.MarshalJSON()
	fmt.Printf("game json = %s\n", string(bs))

	// Connect to all players.
	err_chans := make(map[sirpent.UUID]chan error)
	for player_id, player := range game.Players {
		err_chans[player_id] = make(chan error)
		go player.Connect(game, 5*time.Second, err_chans[player_id])
	}
	for player_id, player := range game.Players {
		err := <-err_chans[player_id]
		if err != nil {
			player.ErrorKillPlayer(err)
		}
	}

	// 1. Syncronously a game state is created with a Snake for each connected Player.
	new_game_state := sirpent.NewGameState(game)
	for player_id, player := range game.Players {
		v, _ := game.Grid.CryptoRandomCell()
		snake := sirpent.NewSnake(v)
		snake = append(snake, game.Grid.CellNeighbour(snake[0], "SOUTHWEST"))
		snake = append(snake, game.Grid.CellNeighbour(snake[1], "SOUTHWEST"))
		new_game_state.Plays[player_id] = sirpent.NewPlayerState(player, snake)
	}
	game.Ticks[game.TickCount] = new_game_state
	game.TickCount++

	play(game)
}

func play(game *sirpent.Game) {
	current_state := game.LatestTick()
	for current_state.HasLivingPlayers() {
		//cs_json, _ := current_state.MarshalJSON()
		//fmt.Printf("current_state json = %s\n", string(cs_json))

		next_state := &sirpent.GameState{
			ID:    game.TickCount,
			Plays: make(map[sirpent.UUID]*sirpent.PlayerState),
			Food:  current_state.Food,
		}

		err_chans := make(map[sirpent.UUID]chan error)
		action_chans := make(map[sirpent.UUID]chan *sirpent.PlayerAction)
		for player_id, current_player_state := range current_state.Plays {
			if current_player_state.Alive {
				err_chans[player_id] = make(chan error)
				action_chans[player_id] = make(chan *sirpent.PlayerAction)
				go current_player_state.Player.PlayTurn(game, action_chans[player_id], err_chans[player_id])
			}
		}

		for player_id, current_player_state := range current_state.Plays {
			if current_player_state.Alive {
				next_player_state := &sirpent.PlayerState{
					Player: current_player_state.Player,
					Snake:  current_player_state.Snake,
				}

				var err error
				var action *sirpent.PlayerAction
				select {
				case err = <-err_chans[player_id]:
					fmt.Printf("Error %s %s\n", player_id, err.Error())
					next_player_state.Player.ErrorKillPlayer(err)
				case action = <-action_chans[player_id]:
					fmt.Printf("Action %s %s\n", player_id, action)
					next_player_state.Snake = current_player_state.Snake.Move(game.Grid, action.Move)
				}

				next_player_state.Action = action
				next_player_state.Alive = next_player_state.Player.Alive
				next_state.Plays[player_id] = next_player_state
			}
		}

		game.Ticks[game.TickCount] = next_state
		game.TickCount++
		current_state = game.LatestTick()
	}
}
