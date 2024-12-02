package com.example.Proj1_2019202050.dto;

import com.example.Proj1_2019202050.domain.entity.File;
import lombok.*;

import java.time.LocalDateTime;

@Getter
@Setter
@ToString
@NoArgsConstructor
public class FileDto //controller와 Service 간 데이터 이동을 위한 틀
{
    private Long id;
    private String title;
    private String content;
    private String origFilename;
    private String filePath;
    private LocalDateTime createdDate;
    private LocalDateTime modifiedDate;

    public File toEntity() {
        File build = File.builder()
                .id(id)
                .title(title)
                .content(content)
                .origFilename(origFilename)
                .filePath(filePath)
                .build();
        return build;
    }
    public int getTitleLength(){
        return title.length();
    }//title 길이 controller에서 예외처리하기 위해 만듦
    public int getCommentLength() {return content.length();}//content 길이 반환

    @Builder
    public FileDto(Long id, String title, String content, String origFilename, String filePath, LocalDateTime createdDate, LocalDateTime modifiedDate) {
        this.id = id;
        this.title = title;
        this.content = content;
        this.origFilename = origFilename;
        this.filePath = filePath;
        this.createdDate = createdDate;
        this.modifiedDate = modifiedDate;
    }
}