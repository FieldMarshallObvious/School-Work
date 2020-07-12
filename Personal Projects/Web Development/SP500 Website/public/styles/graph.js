ej.base.enableRipple(window.ripple)

draw();

async function getData( url ){
    var output;
    const historicalData = await fetch(url);
    var data =  await historicalData.json();

    console.log("The data from the server is ", data.priceHistory);
    return new Promise( (resolve, reject) => 
    {
        setTimeout(() => {
            //Set data if it has not been acquired all ready
            output = data;

            //Check to see if the data has been acquired
            if ( output != undefined )
            {
                resolve(output);
            }
            else 
            {
                reject("Data was not acquired");
            }
        }, 500, output, data);
    });
 }

async function draw()
{
    console.log("In function");
    var data;
    getData(`historicalData/SP500Historical`).then((results) =>
    {

    data = results.priceHistory;
    
    console.log("data is ", data);
    //Create graph object
    console.log("get here");
    renderSplineStockChart = function (SP500) {
        var stockChart = new ej.charts.StockChart({
            primaryXAxis: { valueType: 'DateTime', majorGridLines: { width: 0 }, crosshairTooltip: { enable: true } },
            primaryYAxis: {
                lineStyle: { color: 'transparent' },
                majorTickLines: { color: 'transparent', width: 0 }
            },
            chartArea: { border: { width: 0 } },
            series: [
                {
                    dataSource: SP500, xName: 'x', yName: 'high', type: 'Spline'
                }
            ],
            seriesType : [],
            indicatorType : [],
            title: 'S&P 500 Stock Price',
            titleStyle: { fontWeight: '500', color: '#424242' },
            tooltip: { enable: true },
            crosshair: { enable: true },
            load: function (args) {
                var selectedTheme = location.hash.split('/')[1];
                selectedTheme = selectedTheme ? selectedTheme : 'Material';
                args.stockChart.theme = (selectedTheme.charAt(0).toUpperCase() +
                    selectedTheme.slice(1)).replace(/-dark/i, 'Dark').replace(/contrast/i, 'Contrast');
            },
            tooltipRender: function (args) {
                if  (args.text.split('<br/>')[4]) {
                    var target = parseFloat(args.text.split('<br/>')[4].split('<b>')[1].split('</b>')[0]);
                    var value = (target / 100000000).toFixed(1) + 'B';
                    args.text = args.text.replace(args.text.split('<br/>')[4].split('<b>')[1].split('</b>')[0], value);
                }
            },
        });
        stockChart.appendTo('#HistoricalPrices');
    };

    console.log("After here");
    
    //draw object 
    var SP500;
    var ajax = new ej.base.Ajax(`historicalData/SP500Historical`, 'GET', true);
    console.log("The ajax is ", ajax);
    ajax.send().then();
    ajax.onSuccess = function (data) {
        console.log("In ajax sunction");
        SP500 = JSON.parse(data).priceHistory;
        console.log(SP500);
        console.log('Price history is ', JSON.parse(data).priceHistory);
        SP500.map(function (data) {
            data.x = new Date(data.x);
        });
        renderSplineStockChart(SP500);
    };

    });
}