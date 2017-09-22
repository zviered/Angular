/*************************************************** */
var IsAliveRequest = { 
    id:1,
  };

/**************************************************** */
var ReadInfoRequest = {
    "id":2,
    "device":0
}

/**************************************************** */
var Timing = {
    "PriLength":1,
    "SmcPulseWidth":2
}

/**************************************************** */
var WriteWaveformRequest = {
    "id":3,
    "timing" :[Timing, Timing]
}

export {IsAliveRequest};
export {WriteWaveformRequest};
export {ReadInfoRequest};




