//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/15/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        VStack {
                // Button using a string
                Button("Click Me", action: {
                    print("Hello World!")
                })
                
                // Button using tr ailing closure
                Button("Click Me") {
                    print("Hello World")
                }
            
            // Buton initializer with label view
            Button(action: {
                print("Hello World!")
            }, label: {
                HStack {
                    Image(systemName: "pencil")
                    Text("Edit")
                }
            })
            }
        }
    }

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
