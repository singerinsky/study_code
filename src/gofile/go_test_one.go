package go_test_one

import (
	"fmt"
	"testing"
)

type Hello struct {
	Name string
}

func TestStringTest(t *testing.T) {
	name := "Gladys"
	helloobj := Hello{Name: name}
	fmt.Print(helloobj.Name)
}

type MyMsgStruct struct {
	Age  int
	name string
}

func CreateMsg() MyMsgStruct {
	newMsg := MyMsgStruct{35, "guanlei"}
	return newMsg
}

func TestStruct(t *testing.T) {
	msgOne := CreateMsg()
	fmt.Print(msgOne)
    if msgOne.
}
