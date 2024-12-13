package com.example.Proj2_spr_2019202050;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.data.jpa.repository.config.EnableJpaAuditing;

@EnableJpaAuditing
@SpringBootApplication
public class Proj2_spr_2019202050Application {

	public static void main(String[] args) {
		SpringApplication.run(Proj2_spr_2019202050Application.class, args);
	}
}

