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
                .font(.largeTitle)
            
            Spacer()
            
            // Amount of credits remaining
            Text( "Credits: " + String(credits) )
            
            Spacer()
            
            // Slot images
            HStack {
                Image(left).resizable()
                           .aspectRatio(contentMode: .fit)
                Image(middle).resizable()
                             .aspectRatio(contentMode: .fit)
                Image(right).resizable()
                            .aspectRatio(contentMode: .fit)
            }

            
            Spacer()
            
            Button( action: {
                    // Give slots new images
                    determineImage(&left)
                    determineImage(&middle)
                    determineImage(&right)
                
                    // Determine if you can or lose money
                    if( ( left == right ) && ( right == middle ) )
                    {
                        credits += 15 // Add credits to the balance
                    }
                    else
                    {
                        credits -= 15 // Remove credits from the balance
                    }
                
                    },
                    label: {
                        Text("Spin").padding(.horizontal, 40.0)
                                    .padding(.vertical, 10.0)
                                    .foregroundColor(Color.white)
                                    .background(Rectangle()
                                    .foregroundColor(.blue))
                                    .cornerRadius(15.0)
                  })
            
            Spacer()
            
            
        }
    }
    
    // Assign the image value to the passed variable
    func determineImage( _ image:inout String )
    {
        // Generate random number
        let slotRand = Int.random(in: 1...3)
    
        // Assign correct slot image
        switch slotRand {
        case 2:
            image = "cherry"
            break;
        case 3:
            image = "star"
            break;
        default:
            image = "apple"
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
