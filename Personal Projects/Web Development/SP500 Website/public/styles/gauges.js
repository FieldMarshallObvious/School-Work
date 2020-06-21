ej.base.enableRipple(window.ripple)

createGraph();

async function createGraph()
{
  	//Variable declarations
    var curData;
    var color;
    const curdate = getcurDate();

    console.log('creating graph');

    //Get data from server then convert it to json
    const serverRes = await fetch(`index_key_ratios/SP500`);
    console.log(serverRes);
   	curData = await serverRes.json();

   	//Get PE color
   	color = await getColor(curData.index_pe, 0, 60);

   	//Create PE graph
   	var SP500PE = await linearGauge( curData.index_pe, color );
   	SP500PE.appendTo('#SP500LinearPE');


   	//Get PD color
   	color = await getColor(curData.dividend_yield, 0, 60);

   	//Create PD graph
   	var SP500PD = await linearGauge( curData.dividend_yield, color );
   	SP500PD.appendTo('#SP500LinearPD');


   	//Get SHPE color
   	color = await getColor(curData.shiller_pe, 0, 60);

   	//Create SHPE graph
   	var SP500SHPE = await linearGauge( curData.shiller_pe, color );
   	SP500SHPE.appendTo('#SP500LinearShiller');


   	//Get RadialColor
   	color = await getColor(curData.radial_pos, 0, 100);

   	//Create RadialGraph
   	var SP500Radial = await radialGuage( curData.radial_pos, color);
   	SP500Radial.appendTo('#SP500Radial');
}

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
function linearGauge( curVal, color ) 
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
                content: '<div id="title" style="width:300px;"><p style="font-size:18px;color:black;float:left;margin-left:2px;' + 'margin-top:16em;">P/E Ratio:</p></div>',
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
