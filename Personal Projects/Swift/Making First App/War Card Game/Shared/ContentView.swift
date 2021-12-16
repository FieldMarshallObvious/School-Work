//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/13/21.
//

import SwiftUI

struct ContentView: View {
    @State private var playerCard = "card5"
    @State private var cpuCard = "card9"
    @State private var playerScore = 0
    @State private var cpuScore = 0
    
    var body: some View {
        ZStack {
            Image("background").resizable()
                               .ignoresSafeArea()
                
            VStack {
                Image("logo")
                
                Spacer()
                
                // Card stack
                HStack {
                    Spacer()
                    
                    Image(playerCard)
                    
                    Spacer()
                    
                    Image(cpuCard)
                    
                    Spacer()
                }
                
                Spacer()
                
                Button(action: {
                    // Random number generator
                    // Between 2 and 13
                    let playerRand = Int.random(in: 2...14)
                    let cpuRand = Int.random(in: 2...14)
                    
                    // Update cards
                    playerCard = "card" + String(playerRand)
                    cpuCard = "card" + String(cpuRand)
                    
                    
                    // Update score
                    
                    if (playerRand > cpuRand)
                    {
                        playerScore += 1
                    }
                    else if (playerRand < cpuRand)
                    {
                        cpuScore += 1
                    }
    
                    
                }, label: {
                    Image("dealbutton")
                })
                                
                Spacer()
                
                // Player Scores
                HStack {
                    
                    Spacer()
                    
                    // Player
                    VStack {
                        Text("Player")
                            .font(.headline)
                            .foregroundColor(Color.white)
                        Text(String(playerScore))
                            .font(.largeTitle)
                            .foregroundColor(Color.white)
                    }
                    
                    Spacer()
                    
                    // CPU
                    VStack {
                        Text("CPU")
                            .font(.headline)
                            .foregroundColor(Color.white)
                        Text(String(cpuScore))
                            .font(.largeTitle)
                            .foregroundColor(Color.white)
                    }
                    
                    Spacer()
                }
            }
        }
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
