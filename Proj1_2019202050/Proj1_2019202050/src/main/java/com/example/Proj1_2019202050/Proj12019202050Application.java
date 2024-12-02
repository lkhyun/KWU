package com.example.Proj1_2019202050;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
import org.springframework.data.jpa.repository.config.EnableJpaAuditing;
import org.springframework.web.filter.HiddenHttpMethodFilter;

@EnableJpaAuditing
@SpringBootApplication
public class Proj12019202050Application {

	public static void main(String[] args) {
		SpringApplication.run(Proj12019202050Application.class, args);
	}
	@Bean
	public HiddenHttpMethodFilter hiddenHttpMethodFilter()//put,delete request사용을 위해 사용
	{
		return new HiddenHttpMethodFilter();
	}
}

