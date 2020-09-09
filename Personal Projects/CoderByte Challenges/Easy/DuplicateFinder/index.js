console.log("in script");
function FindIntersection(strArr) { 

    var newArr;
    var num1 = strArr[0].split(',').map(x=>+x);
    var num2 = strArr[1].split(',').map(x=>+x);

    console.log(strArr[0]);
  
    for( i = 0; i < num1.length; i ++ )
    {
      for( j = i - 1; j < num2.length; j++ )
      {
        if( num2[j] == num1[i] )
        {
          if(newArr == undefined)
            newArr = num1[i];
          else
            newArr += "," +  num1[i];
        }
      }
    }
    console.log(strArr[0]); 

    return newArr;  
  }
     
document.getElementById("ButtonPress").addEventListener( "click", function() {
  //Get output element
  var output = document.getElementById("Output");
  
  //Get First array
  var arr1In = document.getElementById("array1").value;

  var temp;


  //Check if each character is a char
  for( i = 0; i < arr1In.length; i++ )
  {
    temp = arr1In.charAt(i);
    if( temp >= '0' && temp <= '9' )
      continue;
    else if( temp == ',' || temp == ' ')
      continue
    else
    {
      output.innerText = "Please enter a valid string! For example 1, 2, 3"
      return;
    }
  }

  var arr2In = document.getElementById("array2").value;

  for( i = 0; i < arr2In; i++ )
  {
    temp = arr2In[i].charAt(i);
    if( temp >= '0' && temp <= '9' )
      continue;
    else if( temp == ',' || temp == ' ')
      continue
    else
    {
      output.innerText = "Please enter a valid string! For example 1, 2, 3"
      return;
    }
  }

  var arrTot = [arr1In.toString(),  arr2In.toString()];




  output.innerHTML = "Output: " + FindIntersection(arrTot);

  return;
});