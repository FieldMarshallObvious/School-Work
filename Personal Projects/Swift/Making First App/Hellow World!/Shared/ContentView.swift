//
//  ContentView.swift
//  Shared
//
//  Created by Noah del Angel on 12/13/21.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        // MARK: Text Elements and modifications
        // Text element . modifier
        // Can in theory have infinite number of modifiers
        //Text("Hello!").padding().background(Color.blue)
        
        // Building using interface using other methods
        
            // CLick and drag from library
            // padding for top
            //Text("Hello!").padding(.top)
        
            // padding for top
            //Text("Hello!").padding(.all)
        
            // creating modifier using insecpection window
            //Text("Hello!").padding(.all).background(/*@START_MENU_TOKEN@*//*@PLACEHOLDER=View@*/Color.blue/*@END_MENU_TOKEN@*/)
        
            // creating modifier using insecpection window
            //Text("Hello!").padding(.all).background(/*@START_MENU_TOKEN@*//*@PLACEHOLDER=View@*/Color.blue/*@END_MENU_TOKEN@*/)
            
            // Changing modifers from preview window
            //Text("Hello!").padding(.all).background(Color.green.blur(radius: /*@START_MENU_TOKEN@*/3.0/*@END_MENU_TOKEN@*/))
        
            // Changing modifiers from code in-line editor
            //Text("Hello!").padding(.all).background(Color.green.blur(radius: /*@START_MENU_TOKEN@*/3.0/*@END_MENU_TOKEN@*/)).cornerRadius(/*@START_MENU_TOKEN@*/3.0/*@END_MENU_TOKEN@*/)
        
        // MARK: Image Elements & Vertical / Horizontal Stacks
        // Note, good practice to start modifiers on new line
        
        // VStack - places elements vertically
        VStack {
            // Spacer - fill all available empty space within object
            Spacer()
            
            Image("logo").resizable()
                         .aspectRatio(contentMode: .fit)
            Spacer()
            
            HStack {
                Spacer()
                
                Text("Hello")
                
                Spacer()
                
                Text("World!")
                
                Spacer()
            }
        }
        
        //HStack - places elements horizontally
        /*HStack {
            Image("logo").resizable()
                         .aspectRatio(contentMode: .fit)
            Text("Hello!")
        }*/
        
        // Zstack - places elements on top of each other
        /*ZStack{
            // Note: elements at the begging of the statement are farthest to the back
            Image("logo").resizable()
                         .aspectRatio( contentMode: .fit)
            // Note: you can embeed stacks within each other
            HStack(spacing: 20.0) {
                Text("Hello")
                Text("World!")
            }
        }*/
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
