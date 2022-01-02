import { BrowserModule } from '@angular/platform-browser';
import { NgModule } from '@angular/core';
import { HttpClientModule } from '@angular/common/http';


import { AppComponent } from './app.component';
import { HelloComponent } from './hello/hello.component';
import { NgServerService } from './ng_server.service';

@NgModule({
  declarations: [
    AppComponent,
    HelloComponent
  ],
  imports: [
    BrowserModule,
    HttpClientModule
  ],
  providers: [NgServerService, { provide: 'mHostAndPort', useValue: '0.0.0.0:5600' }, ],
  bootstrap: [AppComponent]
})
export class AppModule { }
