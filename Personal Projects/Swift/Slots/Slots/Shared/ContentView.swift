//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/16/21.
//

import SwiftUI

struct ContentView: View {
    // Initial credit amount
    @State var credits = 1000
    
    // Initial image starting values
    @State var left = "apple"
    @State var middle = "apple"
    @State var right = "apple"
    
    var body: some View {
        VStack{
            // Title
            Text("SwiftUI Slots!")
            
            Spacer()
            
            // Amount of credits remaining
            Text( "Credits: " + String(credits) )
            
            Spacer()
            
            // Slot images
            HStack {
                Image(left)
                Image(middle)
                Image(right)
            }
            
            Spacer()
            
            
            
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
