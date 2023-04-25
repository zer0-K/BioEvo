import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { BioEvoMainComponent } from './bio-evo-main/bio-evo-main.component';

const routes: Routes = [
  {
    path: '',
    redirectTo: 'bio-evo',
    pathMatch: 'full'
  },
  {
    path: 'bio-evo',
    component: BioEvoMainComponent
  }
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
