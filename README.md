# 物联网硬件SDK使用指南(1.0-BETA)

设备端SDK包含了接入物联网平台的API，源代码，范例代码和文档.

当前SDK的目录结构如下：

``` sh
SOURCE_ROOT
|── enno_api(Source files of the enno IoT device SDK)
|── azure-umqtt-c(communication protocol library, current azure-umqtt only)
|── samples(sample application project for different platforms and protocols)
|── docs(Developer guide & API documentation)
```

## 第一步：编译依赖项目

进入设备SDK目录，一次运行如下命令:

```sh
$cd YOUR_SOURCE_ROOT
$./1-load-azure-umqtt.sh
$./1-load-azure-umqtt.sh
$./3-build-enno.sh
$make
```

这样就完成了所有依赖项的构建。

## 第二步：编译自己的Demo

打开sample/sample_src.c
修改deviceid和token为第一步中记录的设备登录凭据：

```c
enno.host = "shtc.wisiot.com";
enno.port = 1883;
enno.deviceid = "378aacab-be2c-445a-a707-23cdaad04b48";
enno.token = "65c1aa62-527d-4f77-968a-302c9c53427d";
enno.oter = "";
enno.subscrib[0] = "enno/in/json";	// Subscrib two subjects 
enno.subscrib[1] = "enno/out/json/378b8cab-be2c-445a-a707-2389aad04b48";
```

然后进入Sample目录，找到与自己对应的平台，运行make，完成编译。



输出结果为:

```
Connecting to enno server 139.217.10.99:1883...connected.
Subscribing system topic...subscribed.
Send device registeration...sent.
Registered new device
Location updated.
Location updated.
Location updated.
Location updated.

```

## 第三步：验证

```
$./simple_enno
```