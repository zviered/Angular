import { Component } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {Http} from '@angular/http';

import 'rxjs/add/operator/timeout'

import {IsAliveRequest} from '../icd/PcToTgtIcd';
import {WriteWaveformRequest} from '../icd/PcToTgtIcd';
import {ReadInfoRequest} from '../icd/PcToTgtIcd';

import {IsAliveReply} from '../icd/TgtToPcIcd';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})

export class AppComponent {
  title = 'app works!';
  constructor(private http: Http)
  {  
    setInterval(()=> {
      this.sendIsAlive(); },1000); 
    }

    private sendIsAlive ()
    {
      var myJSON = JSON.stringify(IsAliveRequest);
      this.http.post('http://localhost:8000',myJSON)
          .timeout(2000)
          .subscribe ( data => {console.log ('ok=',data.ok);},
                      error => alert ('Error:'+error),
                      () => console.log('END'));
    }
}
