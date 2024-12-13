package com.example.Proj2_spr_2019202050.controller;

import com.example.Proj2_spr_2019202050.dto.FileDto;
import com.example.Proj2_spr_2019202050.service.FileService;
import com.google.gson.Gson;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;

@RestController //전체 컨트롤러
public class BoardController {
    private FileService fileService;//file 저장이나 데이터 로드시 사용하는 서비스 객체

    public BoardController(FileService fileService) {
        this.fileService = fileService;
    }//생성자

    @PostMapping("/info/upload")
    public ResponseEntity<String> savePostData(@RequestBody FileDto fileDto){
        if(fileDto.getTitle().length() > 10){
            return new ResponseEntity<>("title length too long", HttpStatus.BAD_REQUEST);
        }
        if(fileDto.getContent().length() > 100){
            return new ResponseEntity<>("content length too long", HttpStatus.BAD_REQUEST);
        }
        fileService.saveFile(fileDto);
        return new ResponseEntity<>("received successful", HttpStatus.OK);
    }
    @GetMapping("/info/loadAll")
    public String loadPostData(){
        Gson gson = new Gson();
        String json = gson.toJson(fileService.getFileList());
        return json;
    }
    @DeleteMapping("/info/delete")
    public ResponseEntity<String> deletePostData(@RequestBody FileDto fileDto){
        fileService.deletePost(fileDto.getId());
        return new ResponseEntity<>("received successful", HttpStatus.OK);
    }

}
