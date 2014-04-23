/*var initialized = false;

Pebble.addEventListener("ready", function() {
  console.log("ready called!");
  initialized = true;
});

Pebble.addEventListener("showConfiguration", function() {
  console.log("showing configuration");
  Pebble.openURL('https://dl.dropboxusercontent.com/s/eaeua75qgugeyyy/Simple.html?dl=1&token_hash=AAGPpgs7g8G5a_mVCeTNkg3eZpcuFBa3nZyzqnjo1L6Ckg');
});

Pebble.addEventListener("webviewclosed", function(e) {
  console.log("configuration closed");
  var configuration = JSON.parse(e.response);
  var option = configuration["inverted"]
  //Pebble.sendAppMessage("inverted":option)
  console.log("inverted = " + option);
});