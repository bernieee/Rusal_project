//usr/bin/go run $0 $@ ; exit
package main

import(
	"fmt"
	"os"
	"io/ioutil"
	"strings"
	"time"
	"strconv"
)

func main(){
	fmt.Println("Starting error handler ver 0.1")
	files, err := ioutil.ReadDir("./errors")
	check(err)
	for _, file := range files {
		//parse all files
		fmt.Println("########################################")
		fmt.Println("parsing", file.Name())
		f, err := os.Open("./errors/"+file.Name())
		check(err)
		bytePrompt := make([]byte, 128)
		len, err := f.Read(bytePrompt)
		prompt := string(bytePrompt[:len-1])
		chunks := strings.Split(prompt, "_")
		//chunks[0] - ERROR; chunks[1] - DATA/SAT; chunks[2] - unparsed date/time; chunks[3] - IMEI
		//if this is a DATA error
		if(chunks[1] == "DATA") {
			fmt.Println("This is a data error at #"+chunks[3])
			fmt.Println("Most likely, this is a setting error, please restart #"+chunks[3])
		}
		//if this is a SAT error
		if(chunks[1] == "SAT") {
			fmt.Println("This is a sattelite error at #"+chunks[3])
			fmt.Println("Switching time...")
			//fix date/time(from yy/mm/dd,hh:mm:ss)
			dateTime := strings.Split(chunks[2], ",")
			date := strings.Split(dateTime[0], "/")
			timest := strings.Split(dateTime[1], ":")
			trueSec := (timest[2])[:2]
			y, err := strconv.Atoi("20"+date[0])
			check(err)
			m, err := strconv.Atoi(date[1])
			check(err)
			d, err := strconv.Atoi(date[2])
			check(err)
			h, err := strconv.Atoi(timest[0])
			check(err)
			mi, err := strconv.Atoi(timest[1])
			check(err)
			s, err := strconv.Atoi(trueSec)
			check(err)
			t := time.Date(y, time.Month(m), d, h, mi, s, 0, time.UTC)
			fmt.Printf("There's been an error at %v\n", t.Local()) //assuming that time is set correctly
		}
	}
	fmt.Println("########################################")
	//clear error directory if user wants so
	for {
		fmt.Print("Do you want to clear current error directory?[y/n]: ")
		var res string
		fmt.Scanf("%s", &res)
		if(res == "y") {
			for _, file := range files {
				os.Remove("./errors/"+file.Name())
			}
			break
		} else if(res == "n") {
			break
		}
	}
}

func check(e error){
	if e != nil {
		panic(e)
	}
}
