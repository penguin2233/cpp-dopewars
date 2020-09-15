<html>
 <head>
  <title>authserver test</title>
 </head>
 <body>
	 <?php 
	 if(isset($_SERVER['HTTPS']) && $_SERVER['HTTPS'] === 'on') 
    $url = "https"; 
	 else
    $url = "http"; 
	 $url .= "://"; 
	 $url .= $_SERVER['HTTP_HOST']; 
	 $url .= $_SERVER['REQUEST_URI']; 	 
	 $url_components = parse_url($url); 
	 parse_str($url_components['query'], $params); 
	 if($params['key'] == 420)
		 http_response_code(420);
	 else
		 http_response_code(402)
	 ?>
 </body>
</html>
