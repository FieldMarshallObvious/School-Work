//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/13/21.
//

import SwiftUI

struct ContentView: View {
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
                    
                    Image("card10")
                    
                    Spacer()
                    
                    Image("card11")
                    
                    Spacer()
                }
                
                Spacer()
                
                Image("dealbutton")
                
                Spacer()
                
                // Player Scores
                HStack {
                    
                    Spacer()
                    
                    // Player
                    VStack {
                        Text("Player")
                            .font(.headline)
                            .foregroundColor(Color.white)
                        Text("0")
                            .font(.largeTitle)
                            .foregroundColor(Color.white)
                    }
                    
                    Spacer()
                    
                    // CPU
                    VStack {
                        Text("CPU")
                            .font(.headline)
                            .foregroundColor(Color.white)
                        Text("0")
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
