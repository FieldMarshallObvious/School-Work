//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/13/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
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
            
        }
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
