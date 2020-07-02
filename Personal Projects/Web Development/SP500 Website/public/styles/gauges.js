ej.base.enableRipple(window.ripple)

//Global variable
var thirtyminutes =  15 * 60000;

createGraph();

setInterval(updateIndexPrice, thirtyminutes);

//Gets the new price and changes colors based
//on new price relative to old price
async function updateIndexPrice()
{
	//Variable declarations
	var originalColor = getComputedStyle(document.getElementById("SP500Price")).backgroundColor;
	var opacity = 0.7,
		r,g,b;

	const curPriceRes = await fetch(`cur_index_price`);
   	curPrice = await curPriceRes.json();

   	document.getElementById("SP500Price").innerText = "$" + curPrice;

   	//Get curPrice relative to last price
   	const curCompRes = await fetch(`last_index_price_comparisson/${curPrice}`);
   	curComp = await curCompRes.json();

   	//Set div color based on last index price
   	if( curComp == 1 )
   	{
   		r = 0;
   		g = 255;
   		b = 0;
   	}
   	else if( curComp == 0 )
   	{
   		r = 255;
   		g = 247;
   		b = 0;
   	}
   	else
   	{
   		r = 255;
   		g = 0;
   		b = 0;
   	}
   	document.getElementById("SP500PriceContainer").style.backgroundColor = `rgba(${r},${g},${b},${opacity})`;

   	//Return the element to original color after one second
   	setTimeout(async function() 
   	{
   		while( opacity != 0 )
   		{
   			opacity-=0.1;
   			await sleep(50);
   			document.getElementById("SP500PriceContainer").style.backgroundColor = `rgba(${r},${g},${b},${opacity})`;
   		}
   	}, 1000);
}

//This function draws all the gauges and graphs on the index page
async function createGraph()
{
  	//Variable declarations
    var curData;
    var color;
    var content = ['<div id="title" style="width:300px;"><p style="font-size:18px;color:black;float:left;margin-left:2px;' + 'margin-top:16em;">P/E Ratio:</p></div>', 
    			   '<div id="title" style="width:300px;"><p style="font-size:18px;color:black;float:left;margin-left:2px;' + 'margin-top:16em;">Dividend Yield:</p></div>',
    			   '<div id="title" style="width:300px;"><p style="font-size:18px;color:black;float:left;margin-left:2px;' + 'margin-top:16em;">Shiller P/E Ratio:</p></div>'];
    const curdate = getcurDate();


    //Get data from server then convert it to json
    const serverRes = await fetch(`index_key_ratios/SP500`);
   	curData = await serverRes.json();

   	//Get PE color
   	color = await getColor(curData.index_pe, 0, 60);

   	//Create PE graph
   	var SP500PE = await linearGauge( curData.index_pe, color, content[0]);
   	SP500PE.appendTo('#SP500LinearPE');


   	//Get PD color
   	color = await getColor(curData.dividend_yield, 60, 0);

   	//Create PD graph
   	var SP500PD = await linearGauge( curData.dividend_yield, color, content[1] );
   	SP500PD.appendTo('#SP500LinearPD');


   	//Get SHPE color
   	color = await getColor(curData.shiller_pe, 0, 60);

   	//Create SHPE graph
   	var SP500SHPE = await linearGauge( curData.shiller_pe, color, content[2] );
   	SP500SHPE.appendTo('#SP500LinearShiller');


   	//Get RadialColor
   	color = await getColor(curData.radial_pos, 0, 100);

   	//Create RadialGraph
   	var SP500Radial = await radialGuage( curData.radial_pos, color);
   	SP500Radial.appendTo('#SP500Radial');


   	//Change the color the index underline
   	document.getElementById("SP500Underline").style.backgroundColor = `${color}`;


   	//Change value of index price
	updateIndexPrice()


   	//Change the text of the strength box
   	var strengthInfo = textStrength( curData.radial_pos, 50 );

   	document.getElementById("StrengthofEquity").innerText = String.fromCodePoint(strengthInfo[0]) + " " +strengthInfo[1];

   	//Change color of strength box border
   	 document.getElementById("StrengthofEquity").style.borderColor = `${color}`; 

}

//This function gets the color of the particular item
//Then returns the hexcode of that color
async function getColor(curVal, min, max)
{
    //Get data from server
    const serverColorRes = await fetch(`guage_color/${min}, ${curVal}, ${max}`);

    //Convert data to JSON
    const serverColorJS = await serverColorRes.json();

    return serverColorJS;
}


//This function gets the current date from the client
//and returns it
function getcurDate()
{
  var date = new Date,
      year = date.getFullYear(),
      month = (date.getMonth() + 1),
      day = date.getDate();

  if( month <= 10 )
    month = '0' + (date.getMonth() + 1);

  if( day <= 10 )
    day = '0' + date.getDate();

  var curdate = [year, month, day].join('-');

  return curdate;
}

//Function creates linear gauge
function linearGauge( curVal, color, indicator ) 
{
	var gauge = new ej.lineargauge.LinearGauge({
        orientation: 'Horizontal',
        container: {
            width: 30,
            backgroundColor: '#e0e0e0',
            border: {
                width: 0
            },
            offset: -20
        },

        axes: [{
          maximum: 60,
          line: {
            offset: 30
          },
          majorTicks: {
            interval: 0,
          },
          labelStyle: {
            offset: 50
          },
          pointers: [{
            value: 0,
            placement: 'Near',
            offset: -50,
            height: 0,
            width: 0,
            markerType: 'Triangle'
          }],
          ranges: [
          {
            start: 0,
            end: curVal,
            startWidth: 30,
            endWidth: 30,
            color: `${color}`
          }
          ]
        }],
        annotations: [{
                content: indicator,
                axisIndex: 0,
                axisValue: 0,
                x: 150,
                y: -180,
                zIndex: '1'
        }]

    });

	return gauge;
}

//Function creates radial gauge
function radialGuage( curVal, color )
{
    var gauge = new ej.circulargauge.CircularGauge({

        background: "transparent",

        centerY: '70%',

        axes: [{
            lineStyle: { width: 0 },
            startAngle: 270, endAngle: 90,
            radius: '100%',
            labelStyle: { font: { size: '0px' } },
            majorTicks: { width: 0 },
            minorTicks: { height: 0 },
            minimum: 0, maximum: 100,
            ranges: [{
                start: 0, end: 100,
                radius: '90%',
                startWidth: 30, endWidth: 30,
                color: '#E0E0E0'
            }],
            pointers: [{
                type: 'RangeBar',
                value: curVal, radius: '90%',
                color: `${color}`, animation: { duration: 2 },
                pointerWidth: 30
            }]
        }]
    });

    return gauge;
}

//Has the client wat for several seconds
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

function textStrength( curVal, threshold )
{
	//If the value is less than the threshold return
	//a thumbs up
	if( curVal < threshold )
		return ["0x1F44D", "Strong"];

	//If the value is the same as the threshold return
	//a grimmacing tace
	else if( curVal == threshold )
		return ["0x1F62C", "Moderate"];

	//If the value is more than the threshold return
	//a thumbs down
	else
		return ["0x1F44E", "Weak"];

}
