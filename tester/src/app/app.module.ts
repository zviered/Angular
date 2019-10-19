import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
//Following line is mandatory for two way binding
import {FormsModule} from '@angular/forms';
import {MenuModule} from 'primeng/menu'
import {MenubarModule} from 'primeng/menubar';
import { BrowserAnimationsModule } from '@angular/platform-browser/animations';
import {DialogModule} from 'primeng/dialog'
import {DropdownModule} from 'primeng/dropdown';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { ToolbarComponent } from './component/toolbar/toolbar.component';
import { MainComponent } from './component/main/main.component';
import { HttpClientModule } from  '@angular/common/http';
import { FileUploadModule} from 'primeng/fileupload';
import { DataService} from './data.service';

import { PciComponent } from './component/pci/pci.component';
import { MenuComponent } from './component/menu/menu.component';

@NgModule({
  declarations: [
    AppComponent,
    ToolbarComponent,
    MainComponent,
    PciComponent,
    MenuComponent,
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule,
    FileUploadModule,
    //Following line is mandatory for two way binding
    FormsModule,
    MenuModule,
    MenubarModule,
    BrowserModule,
    DropdownModule,
    BrowserAnimationsModule,
    DialogModule,
  ],
  providers: [DataService],
  bootstrap: [AppComponent]
})
export class AppModule { }
