import { Injectable } from '@angular/core';

@Injectable({
  providedIn: 'root'
})
export class DataService {

  public pciObject : any;

  constructor() { 
    console.log ('constructor DataService');
  }

}
