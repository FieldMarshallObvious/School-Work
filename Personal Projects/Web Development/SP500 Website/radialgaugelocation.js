
//Function determines percentage difference between
//actual and historical. Then returns that number
function percentageDifference(actual, historical)
{
	return ((actual-historical)/(historical))*100;
}

//Function gets percentage difference
//Then apply the scales to that number then returns it
function applyScale(actual, historical, scale)
{
	//Variable conversions to int
	actual = parseFloat(actual);
	historical = parseFloat(historical);

	let perDiff = percentageDifference(actual, historical);

	perDiff = perDiff*scale;

	return perDiff
}

//Set this function to be exported
//So it can be called by the server
module.exports = {
	
	//Relates current values to their historical values
	//Then takes those values, after being applied to a scale,
	//Then adds them to the radial guage
	determineGaugeLocation: function ( PE, HistoricalPE, SHPE, HistoricalSHPE, PD, HistoricalPD )
	{
		//Variable declarations
		var PEScale = 0,
			SHPEScale = 0.
			PDScale = 0;

		var scale = 0.3333;

		//Get PE Scale
		PEScale = applyScale( PE, HistoricalPE, scale);

		//Get SHPE Scale
		SHPEScale = applyScale( SHPE, HistoricalSHPE, scale);

		//Get PD 
		PDScale = applyScale ( PD, HistoricalPD, scale );

		//Invert PDScale
		PDScale = -1 * PDScale;

		//Return the sum of all the values
		return PEScale + SHPEScale + PDScale;
	}
}