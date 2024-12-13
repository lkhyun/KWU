package com.example.Proj1_2019202050.controller;

import com.example.Proj1_2019202050.dto.FileDto;
import com.example.Proj1_2019202050.service.FileService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.util.StringUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.multipart.MultipartFile;

import java.io.File;
import java.util.Arrays;
import java.util.List;

@Controller //전체 컨트롤러
public class BoardController {
    private FileService fileService;//file 저장이나 데이터 로드시 사용하는 서비스 객체

    public BoardController(FileService fileService) {
        this.fileService = fileService;
    }//생성자

    @GetMapping(value = {"/", "/index.html"})//index.html화면 요청시
    public String list(Model model) {
        List<FileDto> fileDtoList = fileService.getFileList();//전체 파일 리스트를 서비스 객체를 통해 가져오고
        model.addAttribute("postList",fileDtoList);//모델에 넣어 index.html에서 렌더링함

        return "board/index.html";//index.html 보여주기
    }

    @GetMapping("/post")//글쓰기 버튼 눌렀을 때
    public String post() {
        return "board/upload.html";
    }//upload.html 보여주기
    @PostMapping("/post")// upload.html페이지에서 데이터를 폼에 담아 post요청을 보냈을 때
    public String write(@RequestParam(value = "file", required = false) MultipartFile files, FileDto fileDto) //html에서 file에 해당하는 데이터를 멀티파트 객체로 사용한다는 것, Dto는 Service에 데이터를 보낼 때 사용하는 틀
    {
        try {
            if (files != null && !files.isEmpty()) //file이 첨부되면?
            {
                String origFilename = files.getOriginalFilename();//파일 이름 추출
                String extension = StringUtils.getFilenameExtension(origFilename);//파일 확장자 추출
                if(!isImageExtension(extension))//업로드된 파일이 이미지가 아니면 그냥 index.html으로 돌아감
                {
                    return "redirect:/";
                }
                String savePath = System.getProperty("user.dir") + "\\src/main/resources/static";//현재 프로젝트 폴더의 static에 해당하는 경로
                String filePath = savePath + "\\" + origFilename;//경로에 파일 이름 붙이기
                files.transferTo(new File(filePath));//경로로 파일 전송 이 작업 이후 파일이 static 폴더에 저장됨
                if(fileDto.getTitleLength()>20)//title 20자 넘으면 저장 안함
                {
                    return "redirect:/";
                }
                if(fileDto.getCommentLength()>100)//내용 100자 넘으면 저장 안함
                {
                    return "redirect:/";
                }
                fileDto.setOrigFilename(origFilename);//파일 이름 Dto 틀에 넣기
                fileDto.setFilePath(filePath);//파일 경로 Dto틀에 넣기
                fileService.saveFile(fileDto);//Dto database에 저장,
            }
        }
        catch (Exception e) //예외처리
        {
            e.printStackTrace();
        }
        return "redirect:/";
    }
    @GetMapping("/post/{id}")//index.html에서 게시물 클릭해서 상세 페이지로 이동되었을 때 보여줄 화면
    public String detail(Model model, @PathVariable("id") Long id) //url의 id를 변수로 사용하겠다
    {
        FileDto fileDto = fileService.getFile(id);
        model.addAttribute("post", fileDto);//모델에 넣어 detail.html에서 렌더링함
        return "board/detail.html";
    }
    @GetMapping("/post/edit/{id}")//수정할 때 보여줄 화면
    public String edit(Model model, @PathVariable("id") Long id) {
        FileDto fileDto = fileService.getFile(id);
        model.addAttribute("post", fileDto);//모델에 넣어 edit.html에서 렌더링함
        return "board/edit.html";
    }
    @PutMapping("/post/edit/{id}")//수정 요청
    public String update(@RequestParam(value = "file", required = false) MultipartFile files, @PathVariable("id") Long id, FileDto fileDto) {
        try {
            if (files != null && !files.isEmpty()) //파일 업로드가 수정시 새롭게 되면
            {
                String origFilename = files.getOriginalFilename();
                String extension = StringUtils.getFilenameExtension(origFilename);
                if(!isImageExtension(extension)){
                    return "redirect:/";
                }
                String savePath = System.getProperty("user.dir") + "\\src/main/resources/static";
                String filePath = savePath + "\\" + origFilename;
                files.transferTo(new File(filePath));

                fileDto.setOrigFilename(origFilename);
                fileDto.setFilePath(filePath);
            }
            else //파일 업로드 안했으면 title과 내용만 반영
            {
                FileDto oldFile = fileService.getFile(id);
                fileDto.setOrigFilename(oldFile.getOrigFilename());
                fileDto.setFilePath(oldFile.getFilePath());
            }
            if(fileDto.getTitleLength()>20)
            {
                return "redirect:/";
            }
            if(fileDto.getCommentLength()>100)
            {
                return "redirect:/";
            }
            fileService.saveFile(fileDto);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "redirect:/";
    }
    @DeleteMapping("/post/{id}")//삭제 요청시
    public String delete(@PathVariable("id") Long id)
    {
        fileService.deletePost(id);//id기준으로 삭제
        return "redirect:/";
    }
    private boolean isImageExtension(String extension)//extension을 인자로 받고
    {
        List<String> imageExtensions = Arrays.asList("jpg", "jpeg", "png");
        return imageExtensions.contains(extension.toLowerCase());//위의 확장자 리스트에 존재하지 않는 확장자면 0 반환 존재하면 1 반환, 확장자는 소문자로 통일
    }
}
