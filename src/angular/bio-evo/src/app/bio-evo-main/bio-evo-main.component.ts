import { Component, OnInit } from '@angular/core';
import { BioEvoService } from '../services/bio-evo.service'

@Component({
  selector: 'app-bio-evo-main',
  templateUrl: './bio-evo-main.component.html',
  styleUrls: ['./bio-evo-main.component.css']
})
export class BioEvoMainComponent implements OnInit {
  button_text: string = "time"
  universe_list: string[] = []
  environment_list: string[] = []
  species_list:string[] = []
  environments: Map<string, string[]> = new Map<string, string[]>()
  species: Map<string, string[]> = new Map<string, string[]>()


  constructor(private bio_evo_service: BioEvoService) { }

  ngOnInit(): void {
    this.bio_evo_service.get_info().subscribe(info => { 
      // data is in json format
      var data = JSON.parse(info.replace(/'/g, '"'));

      this.universe_list = data["universes"]

      var envs_json = data["environments"]
      for(var env in envs_json) {
        this.environments.set(env, envs_json[env])
      }

      var species_json = data["individuals"]
      for(var species_ in species_json) {
        this.species.set(species_, species_json[species_])
      }

      debugger
    })
  }

  click_universe(universe_name: string): void {
    debugger
    var envs = this.environments.get(universe_name)
    this.environment_list = envs==null ? [] : envs 
  }
  
  click_environment(environment_name: string): void {
    var species = this.species.get(environment_name)
    this.species_list = species==null ? [] : species
  }

  click_species(species_name: string): void {

  }
}

