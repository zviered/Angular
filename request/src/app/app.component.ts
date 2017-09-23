import { Component } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Http} from '@angular/http';

import 'rxjs/add/operator/timeout'

import {IsAliveRequest} from '../icd/PcToTgtIcd';
import {WriteWaveformRequest} from '../icd/PcToTgtIcd';
import {ReadInfoRequest} from '../icd/PcToTgtIcd';

import {IsAliveReply} from '../icd/TgtToPcIcd';

const BASE_URL = 'http://localhost:8000';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'app works!';
  constructor(private http: Http)
  { 
    //Start timer for sending is alive
    /*setInterval(()=> {
      this.sendIsAlive(); },5000);*/ 
    }
  

    /******************************************************************************* */
    private readInfo ()
    {
      var body = JSON.stringify(ReadInfoRequest);
      this.http.post(`${BASE_URL}`,body).subscribe ( data => {console.log ('readInfo=',data.ok);});
    }

    /******************************************************************************* */
    private writeWaveform ()
    {
      var body = JSON.stringify(WriteWaveformRequest);
      this.http.post(`${BASE_URL}`,body).subscribe ( data => {console.log ('writeWaveform=',data.ok);});
    }

    /******************************************************************************* */
    private sendIsAlive ()
    {
      var myJSON = JSON.stringify(IsAliveRequest);
      this.http.post(`${BASE_URL}`,myJSON)
          .timeout(2000)
          .subscribe ( data => {console.log ('ok=',data.ok);},
                      //error => alert ('Error:'+error),
                      error => console.log ('error=' + error),
                      () => console.log('END'));
    }
}
