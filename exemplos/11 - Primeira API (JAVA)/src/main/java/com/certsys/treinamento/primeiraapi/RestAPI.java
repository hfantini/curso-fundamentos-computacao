package com.certsys.treinamento.primeiraapi;

import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class RestAPI
{
    int clickCount = 0;

    @CrossOrigin
    @GetMapping("/counter")
    public int getClickCount()
    {
        return clickCount;
    }

    @CrossOrigin
    @PostMapping("/counter")
    public void addClickCount()
    {
        clickCount++;
    }
}
