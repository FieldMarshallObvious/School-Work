//Check if the current item has been
//passed based on iterator
function passedCheck(counter, min, max)
{
	var output = false;

	if( min < max )
		if( counter > max )
			output = true;
	if( min > max )
		if( counter < max )
			output = true;
	return output;
}

//Convert RGB value to HEX value
//and return
const rgbToHex = (r, g, b) => '#' + [r, g, b].map(x => {
  const hex = x.toString(16)
  return hex.length === 1 ? '0' + hex : hex
}).join('');

//Determine if the passed value is within the RGB range
//Return true if it is, false if it is not
function checkBounds(value) { return ( value >= 0 && value <= 255 ) }

//determine RGB value and pass
function rgbWheel(min, max, middle)
{	
	//Set variables to ints
	min = parseInt(min);
	max = parseInt(max);
	middle = parseInt(middle);

	//Variable declarations
	var r = 0,
		g = 0,
		b = 0;

	var iterator,
		multiple = 12;
	var iteratorR = 0,
		iteratorG = 0;
	var counter = min;


	//If the min is less than the max 
	//set red to the max and green to zero
	if(min < max)
	{
		r = 0;
		g = 255;

		iterator = 1;

		//Set color iterators
		iteratorR = 1;
		iteratorG = -1;
	}

	//If the min is greater than the max
	//set green to 
	if( min > max )
	{
		r = 255;
		g = 0;

		iterator = -1;

		//Set color iterators
		iteratorR = -1;
		iteratorG = 1;
	} 

	//Determine the RGB value of the gauge based on the location
	//of the guage
	while(counter != max && !( passedCheck( counter, min, max ) ) )
	{
		//min < max branch
		if( min < max )
		{	//Green to yellow gradient if min < max
			if( counter <= middle/2 && min < max )
			{
				//If the next iteration of r does not leave the R range
				if( checkBounds( ( r + iteratorR * multiple ) ) )
					r += iteratorR * multiple;
			}
		
			//Yellow to red gradient if min < max
			else
			{

				if( checkBounds( ( g + iteratorG * multiple ) ) )
					g += iteratorG * multiple;
			}
		}

		//min > max branch
		else
		{
			//Green to yellow gradient if min > max
			if ( counter >= middle/2 && min > max  )
			{
				if( checkBounds( ( g + iteratorG * multiple ) ) )
					g += iteratorG * multiple;
			}

			//Yellow to red gradient min > max
			else
			{
				if( checkBounds( ( r + iteratorR * multiple ) ) )
					r += iteratorR * multiple;
			}
		}

		counter+=iterator;
	}
	return [r, g, b];
}

//Set the function to be called by the server
module.exports = {
	//Call the above two functions and return value
	determineGuageColor: function (min, max, middle)
	{
		const [r, g, b] = rgbWheel(min, max, middle);
		const color = rgbToHex(r, g, b);

		return color;
	}
}