function Decoder(bytes, port) {
	var decoded = {};
  
	var msg = String.fromCharCode.apply(null, bytes);
	  var i = 1; 
	  var temp = '';
	  var hum = '';
	  var pres = '';
	  var light = '';
	  var moisture ='';
	  
	  while(i < msg.length && msg[i] != "H")
	  {
		temp += msg[i];
		i++;
	  }
	decoded.temp = temp;
	
	i++;
	
	while(i < msg.length && msg[i] != "P")
	  {
		hum += msg[i];
		i++;
	  }
	decoded.hum = hum;
	
	i++;
	
	while(i < msg.length && msg[i] != "L")
	  {
		pres += msg[i];
		i++;
	  }
	decoded.pres = pres;
	
	i++;
	
	while(i < msg.length && msg[i] != "M")
	  {
		light += msg[i];
		i++;
	  }
	decoded.light = light;
	
	i++;
	
	while(i < msg.length)
	  {
		moisture += msg[i];
		i++;
	  }
	decoded.moisture = moisture;
	
	i++;
	
	return decoded;
  }