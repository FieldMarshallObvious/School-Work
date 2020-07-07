ej.base.enableRipple(window.ripple)

draw();

function getData( url ){
    const historicalData = await fetch(url);
    var data =  await historicalData.json();
    return data;
 }

function draw()
{
    console.log("In function");
    var data = getData(`historicalData/SP500`);
    let chart = new ej.stockChart.Spline({
        primaryXAxis: { valueType: 'DateTime', majorGridLines: { width: 0 }, crosshairTooltip: { enable: true }},
        primaryYAxis: {
            lineStyle: { color: 'transparent' },
            majorTickLines: { color: 'transparent', width: 0 },
        },
        chartArea: { border: { width: 0 } },
        series: [
            {
                dataSource: data, xName: 'x', yName: 'high', type: 'Spline'
            }
        ],
        tooltip: { enable: true },
        crosshair: { enable: true },
        seriesType : [],
        indicatorType : [],
        title: 'S&P 500 Chart',
    });
    stockChart.appendTo('#HistoricalPrices');
}
