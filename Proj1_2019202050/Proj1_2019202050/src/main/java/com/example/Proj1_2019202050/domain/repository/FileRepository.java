package com.example.Proj1_2019202050.domain.repository;

import com.example.Proj1_2019202050.domain.entity.File;
import org.springframework.data.jpa.repository.JpaRepository;

public interface FileRepository extends JpaRepository<File, Long>//JpaRepository 사용
{
}