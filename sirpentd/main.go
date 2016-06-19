package main

import (
	"fmt"
	"time"
	// "sync"
	"github.com/Taneb/sirpent"
	"github.com/satori/go.uuid"
	"golang.org/x/net/websocket"
	"net/http"
)

func main() {
	grid := &sirpent.Grid{Radius: 30, Origin: sirpent.AxialVector{Q: 0, R: 0}}

	players := make(map[uuid.UUID]*sirpent.Player)
	player0 := sirpent.NewPlayer("localhost:8901")
	players[player0.ID] = player0
	player1 := sirpent.NewPlayer("localhost:8902")
	players[player1.ID] = player1
	/*player2 := sirpent.NewPlayer("localhost:8903")
	players[player2.ID] = player2
	player3 := sirpent.NewPlayer("localhost:8904")
	players[player3.ID] = player3
	player4 := sirpent.NewPlayer("localhost:8905")
	players[player4.ID] = player4
	player5 := sirpent.NewPlayer("localhost:8906")
	players[player5.ID] = player5
	player6 := sirpent.NewPlayer("localhost:8907")
	players[player6.ID] = player6
	player7 := sirpent.NewPlayer("localhost:8908")
	players[player7.ID] = player7
	player8 := sirpent.NewPlayer("localhost:8909")
	players[player8.ID] = player8*/

	game := sirpent.NewGame(grid, players)

	// Connect to players.
	// @TODO: Prevent waiting for network N times, using sync.WaitGroup and Goroutines.
	for _, player := range game.Players {
		err := player.ConnectToPlayer()
		if err != nil {
			// @TODO: Decide how to handle connection unestablished.
			panic("Player connection failed.")
		}
	}
	// @TODO: Tell players about game, grid etc!

	// @TODO: Basic setup complete; start API server.
	//        Expand upon api.go
	api := sirpent.API{}

	go func() {
		http.Handle("/", http.FileServer(http.Dir("webroot")))
		http.Handle("/worlds/live.json", websocket.Handler(func(ws *websocket.Conn) {
			defer func() {
				err := ws.Close()
				if err != nil {
					fmt.Printf("websocket.Close err=%s\n", err)
				}
			}

			api.Websockets = append(api.Websockets, ws)
			// @TODO: Keep Websocket alive without an infinite loop.
			// Use channels properly?
			for {
			}
		}))
		err := http.ListenAndServe(":8080", nil)
		if err != nil {
			panic("ListenAndServe: " + err.Error())
		}
	}()

	// Begin the game.
	for {
		fmt.Printf("Tick %d\n", game.TickCount)

		latest_state := game.Tick()

		for i := range api.Websockets {
			err := websocket.JSON.Send(api.Websockets[i], latest_state)
			if err != nil {
				fmt.Printf("%+v\n", err)
			}
		}

		if !latest_state.HasLivingPlayers() {
			break
		}

		time.Sleep(100 * time.Millisecond)
	}
}
