package com.example.Proj1_2019202050.service;

import com.example.Proj1_2019202050.domain.entity.File;
import com.example.Proj1_2019202050.domain.repository.FileRepository;
import com.example.Proj1_2019202050.dto.FileDto;
import org.springframework.data.domain.Sort;
import org.springframework.stereotype.Service;

import javax.transaction.Transactional;
import java.util.ArrayList;
import java.util.List;

@Service
public class FileService {
    private FileRepository fileRepository;//객체 생성

    public FileService(FileRepository fileRepository) {
        this.fileRepository = fileRepository;
    }//생성자

    @Transactional//트랜잭션으로 선언하므로서 데이터베이스를 단독으로 사용할 수 있게 됨
    public Long saveFile(FileDto fileDto) {
        return fileRepository.save(fileDto.toEntity()).getId();
    }

    @Transactional
    public List<FileDto> getFileList() {
        List<File> fileList = fileRepository.findAll(Sort.by(Sort.Direction.DESC,"createdDate"));//가장 최근 생성된 게시물부터 보여주기 위한 정렬
        List<FileDto> fileDtoList = new ArrayList<>();//데이터 담을 곳

        for(File file : fileList) //controller로 보내기 위해 Dto에 담고
        {
            FileDto fileDto = FileDto.builder()
                    .id(file.getId())
                    .title(file.getTitle())
                    .content(file.getContent())
                    .origFilename((file.getOrigFilename()))
                    .filePath(file.getFilePath())
                    .createdDate(file.getCreatedDate())
                    .modifiedDate(file.getModifiedDate())
                    .build();
            fileDtoList.add(fileDto);//dto를 List에 담고
        }
        return fileDtoList;//리스트 반환 이로써 모든 데이터베이스 내 게시물 데이터를 index.html에 렌더링할 수 있게됨
    }
    @Transactional
    public FileDto getFile(Long id) //id값으로 해당하는 게시물을 데이터베이스에서 찾고 Dto형태로 반환
    {
        File file = fileRepository.findById(id).get();

        FileDto fileDto = FileDto.builder()
                .id(id)
                .title(file.getTitle())
                .content(file.getContent())
                .origFilename(file.getOrigFilename())
                .filePath(file.getFilePath())
                .build();
        return fileDto;
    }
    @Transactional
    public void deletePost(Long id) {
        fileRepository.deleteById(id);
    }//id를 이용해 게시물 데이터베이스에서 삭제
}