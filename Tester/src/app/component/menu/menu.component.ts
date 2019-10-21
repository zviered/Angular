import { Component, OnInit, ElementRef, ViewChild } from '@angular/core';
import {MenuItem} from 'primeng/api';
import {HttpClient} from '@angular/common/http';
import {DataService} from 'src/app/service/data.service'
import { PciComponent } from '../pci/pci.component';

@Component({
  selector: 'app-menu',
  templateUrl: './menu.component.html',
  styleUrls: ['./menu.component.scss']
})
export class MenuComponent implements OnInit {

  items: MenuItem[];
  @ViewChild('fileInput', {static: false}) fileInputRef: ElementRef;

  /********************************************************************/
  constructor(private http: HttpClient, private svc: DataService) {
    console.log ('constructor MenuComponent');
  }

  /********************************************************************/
  public onPci ()
  {
    let pciObject : PciComponent = this.svc.pciObject;

    pciObject.showDialog ();
  }

  /********************************************************************/
  public OnFileSelected (event)
  {
    let fileList: FileList = event.target.files;

    this.http.get ('http://localhost:80/api/'+fileList[0].name,{ responseType: 'text' }).subscribe(
      (val) => {
          console.log("GET call successful value returned in body", 
                      val);
      },
      response => {
          console.log("GET call in error", response);
      },
      () => {
          console.log("The GET observable is now completed.");
      }); 

  }
  
  /********************************************************************/
  public onOpenFile (event) 
  {
    //open select file dialog
    this.fileInputRef.nativeElement.click (event);

    /*var xmlDoc;
    var parser;
    var text = "<bookstore><book>" +
                "<title>Everyday Italian</title>" +
                "<author>Giada De Laurentiis</author>" +
                "<year>2005</year>" +
                "</book></bookstore>";

    var textJson = '{ "employees" : [' +
    '{ "firstName":"John" , "lastName":"Doe" },' +
    '{ "firstName":"Anna" , "lastName":"Smith" },' +
    '{ "firstName":"Peter" , "lastName":"Jones" } ]}';

    parser = new DOMParser();
    xmlDoc = parser.parseFromString(text,"text/xml");
    console.log('xmldoc');
    console.log(xmlDoc);

    console.log('jsonDoc');
    var jsonDoc = JSON.parse(textJson);
    console.log (jsonDoc);*/

    /*this.http.get ('http://localhost:80/api/dwell.xml',{ responseType: 'text' }).subscribe(
      (val) => {
          console.log("GET call successful value returned in body", 
                      val);
      },
      response => {
          console.log("GET call in error", response);
      },
      () => {
          console.log("The GET observable is now completed.");
      });  */
  }

  /********************************************************************/
  ngOnInit() {
    this.items = [
      {
        label: 'File',
        items: [
            {label: 'Open',
            command: () => this.onOpenFile(event)} 
        ]
    },
    {
        label: 'View',
        items: [
            {label: 'Pci',
            command: () => this.onPci ()},
        ]
    }
  ];
  }
}
