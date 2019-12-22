Page({
  data: {
    order:''
  },
choice1:function()
{
  wx.request({
    url: 'https://api.heclouds.com/devices/562233664/datapoints?type=3',
    method: 'post',
    header: {
      //"content-type": "application/x-www-form-urlencoded",
      "api-key": "7AHL6HLQEDOSQtTzwBMjw7kEuaw=",
    },
    success: function (res) {
      //console.log(util.formatTime)
       console.log(res)
    },
    data: {
      order:"coffee",
      
    },
  })
  
  wx.showModal({

    content: `亲，请确定返回寝室的时间！`

  })
},
  choice2: function () {
    wx.request({
      url: 'http://api.heclouds.com/devices/562233664/datapoints?type=3',
      method: 'post',
      header: {
        //"content-type": "application/x-www-form-urlencoded",
        "api-key": "7AHL6HLQEDOSQtTzwBMjw7kEuaw=",
      },
      success: function (res) {
        //console.log(util.formatTime)
        console.log(res)
      },
      data: {
        order: "pearl milk tea",

      },
    })

    wx.showModal({

      content: `亲，请确定返回寝室的时间！`

    })
  },
  choice3: function () {
    wx.request({
      url: 'http://api.heclouds.com/devices/562233664/datapoints?type=3',
      method: 'post',
      header: {
        //"content-type": "application/x-www-form-urlencoded",
        "api-key": "7AHL6HLQEDOSQtTzwBMjw7kEuaw=",
      },
      success: function (res) {
        //console.log(util.formatTime)
        console.log(res)
      },
      data: {
        order: "green tea",

      },
    })
      wx.showModal({

        content: `亲，请确定返回寝室的时间！`

      })
    },
    
      
  choice4: function () {
        wx.request({
          url: 'http://api.heclouds.com/devices/562233664/datapoints?type=3',
          method: 'post',
          header: {
            //"content-type": "application/x-www-form-urlencoded",
            "api-key": "7AHL6HLQEDOSQtTzwBMjw7kEuaw=",
          },
          success: function (res) {
            //console.log(util.formatTime)
            console.log(res)
          },
          data: {
            order: "red tea",

          },
        })

       

    wx.showModal({

      content: `亲，请确定返回寝室的时间！`

    })
  },
send:function()
{

  var theBaiDuAPPkey = "zqBNM8zW1mk2DOX9MMt0CCQL55RobFdy"    //百度的AK, 此处要替换为你自己的APPKey

  //调用百度天气API
  wx.request({
    url: 'https://api.map.baidu.com/telematics/v3/weather?location=%E5%8C%97%E4%BA%AC&output=json&ak=' + theBaiDuAPPkey, //百度天气API

    success: (res) => {
      console.log(`APPKey: ${theBaiDuAPPkey}`, res.data)
      // 利用正则字符串从百度天气API的返回数据中截出今天的温度数据
      try {
        var str = res.data.results[0].weather_data[0].date;
        var tmp1 = str.match(/实时.+/);
        var tmp2 = tmp1[0].substring(3, tmp1[0].length - 2);
        var tmp = +tmp2;
      } catch (e) {
        throw new Error(e)
      }
      if (tmp <10 ) {
          wx.showModal({
            
            content: `当前温度${tmp}度,来杯暖到心坎里的奶茶吧`
          })
      }
    }
  })
},
})
    