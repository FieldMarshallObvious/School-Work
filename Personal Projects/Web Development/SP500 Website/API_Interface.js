//This function formats the given data for a desirable response for JSON formatd
function dividendYield (jsonData)
{
	const output = {
		date: jsonData.dataset.data[0][0],
		yield: jsonData.dataset.data[0][1]
	};


	return output;
}


//Set this function to be exported
//So it can be called by the server
module.exports = {
	//Gets all SP500 data and returns it to the server
	returnSP500: async function ( curdate, APIKey, serverfetch )
	{
		//Variable declarations
		const index = `SP500`;
		var divoutput;
		var curShiller,
			curPE;
		
		//Shiller PE ratio per month
		//Get URL for API
		const shillerPEMonthUrl = `https://www.quandl.com/api/v3/datasets/MULTPL/SHILLER_PE_RATIO_MONTH.json?api_key=${APIKey}`;

		//Get data from API
		const shillerPEMonthRes = await serverfetch(shillerPEMonthUrl);

		//Convert the data to JSON
		const shillerPEMonthJS = await shillerPEMonthRes.json();

		//Find the shiller 
	    shillerPEMonthJS.dataset.data.forEach(element => 
	    {
	      if(element[0].substr(0, 7) == curdate.substr(0,7) || element[0].substr(0, 7) == shillerPEMonthJS.dataset.newest_available_date.substr(0, 7) )
	      {
	        curShiller = element[1];
	      }
	    });


		//PE ratio per month
		//get URL for API
		const indexPEMonthUrl = `https://www.quandl.com/api/v3/datasets/MULTPL/${index}_PE_RATIO_MONTH.json?api_key=${APIKey}`;

		//Get data from API
		const indexPEMonthRes = await serverfetch(indexPEMonthUrl);

		//Convert data to JSON
		const indexPEMonthJS = await indexPEMonthRes.json();

		//Find the shiller 
	    indexPEMonthJS.dataset.data.forEach(element => 
	    {
	      if(element[0].substr(0, 7) == curdate.substr(0,7) || element[0].substr(0, 7) == shillerPEMonthJS.dataset.newest_available_date.substr(0, 7) )
	      {
	        curPE = element[1];
	      }
	    });


		//Get data for dividend yield
		//Get URL for API
		var dividendYieldDayUrl = `https://www.quandl.com/api/v3/datasets/MULTPL/${index}_DIV_YIELD_MONTH?start_date=${curdate}&end_date=${curdate}&api_key=${APIKey}`;

		//Get data from the API
		var dividendYieldDayRes = await serverfetch(dividendYieldDayUrl);
		
		//Convert the data to JSON
		var dividendYieldDayJS = await dividendYieldDayRes.json();


		newest_available_date = dividendYieldDayJS.dataset.newest_available_date;

		//If the most recent update does not equal the current date set the date to the most recent update
		if( dividendYieldDayJS.dataset.newest_available_date != curdate )
		{
			//set curdate to the most recent update for the index
			curdate = dividendYieldDayJS.dataset.newest_available_date;
			
			//Get data for the most recent data
			dividendYieldDayUrl= `https://www.quandl.com/api/v3/datasets/MULTPL/${index}_DIV_YIELD_MONTH?start_date=${curdate}&end_date=${curdate}&api_key=${APIKey}`;
			dividendYieldDayRes = await serverfetch(dividendYieldDayUrl);
			dividendYieldDayJS = await dividendYieldDayRes.json();

			divoutput = dividendYield(dividendYieldDayJS);
		}
		else
		{
			divoutput = dividendYield(dividendYieldDayJS);
		}


		const output = {
			index_pe: curPE,
			shiller_pe: curShiller,
			dividend_yield: divoutput.yield,
			index: index
		};

		return output;
	}
}