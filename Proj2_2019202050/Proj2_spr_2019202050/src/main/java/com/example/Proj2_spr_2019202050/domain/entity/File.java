package com.example.Proj2_spr_2019202050.domain.entity;

import lombok.AccessLevel;
import lombok.Builder;
import lombok.Getter;
import lombok.NoArgsConstructor;
import org.springframework.data.annotation.CreatedDate;
import org.springframework.data.jpa.domain.support.AuditingEntityListener;

import javax.persistence.*;
import java.time.LocalDateTime;

@Getter //File내 데이터를 얻을 때 쓰는 함수를 세팅해줌
@Entity //데이터베이스에 저장할 테이블이다.
@NoArgsConstructor(access = AccessLevel.PROTECTED)//기본 생성자 생성해줌, 멤버변수 세팅에 값이 누락되었을 때를 대비하여 AccessLevel.PROTECTED사용
@EntityListeners(AuditingEntityListener.class)//entity의 변화 감지, id나 게시물 생성시간을 세팅하는 타이밍을 위해 사용
public class File {

    @Id
    @GeneratedValue //값 생성해줌
    private Long id;

    @Column(length = 20, nullable = false)//필수 입력 조건임 null 안됨
    private String title;

    @Column(columnDefinition = "TEXT", nullable = false)
    private String content;
    @Column(nullable = false)
    private String photoPath;

    @CreatedDate//시간 생성해줌
    @Column(updatable = false)//처음 생성하면 수정 안됨
    private LocalDateTime createdDate;

    @Builder//변수 세팅
    public File(Long id, String title, String content, String photoPath) {
        this.id = id;
        this.title = title;
        this.content = content;
        this.photoPath = photoPath;
    }
}