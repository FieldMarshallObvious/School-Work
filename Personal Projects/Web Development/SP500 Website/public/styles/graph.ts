import { enableRipple } from '@syncfusion/ej2-base';
enableRipple(true);

import { StockChart } from '@syncfusion/ej2-charts';
import { DateTime, AreaSeries, CandleSeries, HiloOpenCloseSeries, HiloSeries, LineSeries, SplineSeries  } from '@syncfusion/ej2-charts';
import { AccumulationDistributionIndicator, AtrIndicator, BollingerBands, EmaIndicator, MomentumIndicator } from '@syncfusion/ej2-charts';
import { MacdIndicator, RsiIndicator, Trendlines, SmaIndicator, StochasticIndicator, Export } from '@syncfusion/ej2-charts';
import { TmaIndicator, RangeTooltip, Tooltip, Crosshair , IStockChartEventArgs, ChartTheme} from '@syncfusion/ej2-charts';
StockChart.Inject(DateTime, AreaSeries, CandleSeries, HiloOpenCloseSeries, HiloSeries, LineSeries, SplineSeries);
StockChart.Inject(AccumulationDistributionIndicator, AtrIndicator, BollingerBands, EmaIndicator, MomentumIndicator);
StockChart.Inject(MacdIndicator, RsiIndicator, SmaIndicator, StochasticIndicator);
StockChart.Inject(Trendlines, TmaIndicator, RangeTooltip, Tooltip, Crosshair, Export);

draw();

const getData = async( url: string ): Promise<JSON> => {
    const historicalData = await fetch(url);
    var data =  await historicalData.json();
    return data;
 }

function draw()
{
    console.log("In function");
    var data = getData(`historicalData/SP500`);
    let stockChart: StockChart = new StockChart({
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
        title: 'AAPL Stock Price',
        load: (args: IStockChartEventArgs) => {
            let selectedTheme: string = location.hash.split('/')[1];
            selectedTheme = selectedTheme ? selectedTheme : 'Material';
            args.stockChart.theme = <ChartTheme>(selectedTheme.charAt(0).toUpperCase() +
                selectedTheme.slice(1)).replace(/-dark/i, 'Dark').replace(/contrast/i,  'Contrast');
        }
    });
    stockChart.appendTo('#HistoricalPrices');
}
