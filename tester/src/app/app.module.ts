import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { FormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import {BrowserAnimationsModule} from '@angular/platform-browser/animations';
import { MdMenuModule } from '@angular/material';
import {
  RouterModule,
  Routes
} from '@angular/router';

import { AppComponent } from './app.component';
import { RcmComponent } from './rcm/rcm.component';
import { ExciterComponent } from './exciter/exciter.component';

const routes: Routes = [
  // basic routes
  { path: 'rcm', component: RcmComponent },
  { path: 'exciter', component: ExciterComponent },
];

@NgModule({
  declarations: [
    AppComponent,
    RcmComponent,
    ExciterComponent
  ],
  imports: [
    BrowserModule,
    BrowserAnimationsModule,
    FormsModule,
    HttpClientModule,
    MdMenuModule,
    RouterModule.forRoot(routes), // <-- routes
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
