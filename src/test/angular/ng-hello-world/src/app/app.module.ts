import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';


import { AppComponent } from './app.component';
import { NgStribohCltComponent } from './ng-striboh-clt/ng-striboh-clt.component';
import { NgServerService } from './ng_server.service';

@NgModule({
  declarations: [
    AppComponent,
    NgStribohCltComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule
  ],
  providers: [NgServerService, { provide: 'mHostAndPort', useValue: '127.0.0.1:5600' }, ],
  bootstrap: [AppComponent]
})
export class AppModule { }
