import json


def write_json(content: dict, file_path: str) -> None:
    print(type(content))
    with open(file_path, "w+", encoding="utf-8") as fp:
        print(content)
        # json.dump(content, fp, indent=4)
        json.dump(obj=content,fp=fp,indent=4)



def load_json(file_path: str) -> dict:
    with open(file_path, 'r') as fp:
        content = json.load(fp)
    return content


def test(input_str: str) -> int:
    print(input_str)
    return 1

if __name__ =="__main__":
    content={'one':1, 'two':{2.1:['a', 'b']}}
    write_json(content,'./test.json')