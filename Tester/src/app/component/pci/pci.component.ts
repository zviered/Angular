import { Component, OnInit } from '@angular/core';
import {HttpClient} from '@angular/common/http';
import {WritePciRequest} from '../../../icd/WritePci'
import {ReadPciRequest } from 'src/icd/ReadPci';
import {DataService} from 'src/app/service/data.service'

const BASE_URL = 'http://localhost:8000';

@Component({
  selector: 'app-pci',
  templateUrl: './pci.component.html',
  styleUrls: ['./pci.component.scss']
})
export class PciComponent implements OnInit {

  display: boolean = false;

  writeBar: number;
  writeOffset: string;
  writeData: string;

  readBar: number;
  readOffset: string;
  readData: number;

  writePciRequest : WritePciRequest;
  readPciRequest : ReadPciRequest;
  
  /********************************************************************/
  constructor(private http: HttpClient, private svc: DataService) 
  { 
    console.log ('constructor PciComponent');
    this.writePciRequest = new WritePciRequest;
    this.readPciRequest = new ReadPciRequest;

    this.readBar = 0;
    this.writeBar = 0;

    this.writeOffset = '0x0';
    this.writeData = '0x0';

    this.readOffset = '0x0';

    svc.pciObject = this;
  }

  /********************************************************************/
  public showDialog() {
    this.display = true;
  }

  /********************************************************************/
  public onPciWrite()
  {
    this.writePciRequest.Bar = this.writeBar;
    this.writePciRequest.Data = parseInt(this.writeData);
    this.writePciRequest.Offset = parseInt(this.writeOffset);
 
    console.log (this.writePciRequest);

     var body = JSON.stringify(this.writePciRequest);
    this.http.post (`${BASE_URL}`,body).subscribe(
      (val) => {
          console.log("POST call successful value returned in body", 
                      val);
      },
      response => {
          console.log("POST call in error", response);
      },
      () => {
          console.log("The POST observable is now completed.");
      });        
  }
  
  /********************************************************************/
  public onPciRead()
  {
    this.readPciRequest.Bar = this.readBar;
    this.readPciRequest.Offset = parseInt(this.readOffset);
 
    console.log (this.readPciRequest);

    var body = JSON.stringify(this.readPciRequest);
    this.http.post (`${BASE_URL}`,body).subscribe(
      (val) => {
          console.log("POST call successful value returned in body", 
                      val);
          this.readData = val[3];
      },
      response => {
          console.log("POST call in error", response);
      },
      () => {
          console.log("The POST observable is now completed.");
      });        
  }

  /********************************************************************/
  ngOnInit() {
  }

}
