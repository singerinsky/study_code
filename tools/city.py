import requests
from bs4 import BeautifulSoup
# -*- coding: UTF-8 -*-

provincer = dict()
city = dict()
per_url = "http://www.stats.gov.cn/tjsj/tjbz/tjyqhdmhcxhfdm/2021/"


def get_all_block(city, url):
    print(1)


def get_all_city(provinceter, p_url):
    response = requests.get(p_url)
    content = response.content
    after_decode = str(content, 'utf-8')
    soup = BeautifulSoup(after_decode, 'lxml')
    all_city = soup.select('.citytr')
    for city in all_city:
        print(city.text)


def get_all_prv():
    url = "http://www.stats.gov.cn/tjsj/tjbz/tjyqhdmhcxhfdm/2021/index.html"
    response = requests.get(url)
    content = response.content
    after_decode = str(content, 'utf-8')
    soup = BeautifulSoup(after_decode, 'lxml')
    # data = soup.select('#syno-nsc-ext-gen3 > table:nth-child(3) > tbody > tr:nth-child(1) > td > table > tbody > tr:nth-child(2) > td > table > tbody > tr > td > table > tbody > tr:nth-child(4) > td:nth-child(1) > a')
    # data = soup.select('.provincetr')
    all_p = soup.find_all('a', href=True)
    del all_p[31]
    # for a in soup.find_all('a', href=True):
    for a in all_p:
        print(a.text)
        print("Found the URL:", a['href'])
        print('get city in provincetr')
        provinceter_url = per_url+a['href']
        provincer[a.text] = a['href']
        get_all_city(a.text, provinceter_url)
        break
    # data = soup.select('a')
    # del data[31]
    # print(data)


if __name__ == '__main__':
    get_all_prv()
