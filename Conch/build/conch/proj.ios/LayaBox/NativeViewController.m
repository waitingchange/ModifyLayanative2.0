//
//  NativeViewController.m
//  LayaBox
//
//  Created by captain on 2021/5/19.
//  Copyright © 2021 LayaBox. All rights reserved.
//

#import "NativeViewController.h"
#import "AppDelegate.h"

@interface NativeViewController ()

@end

@implementation NativeViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    UIButton *button = [UIButton buttonWithType:UIButtonTypeCustom];
    [button setBackgroundColor:[UIColor redColor]];
    [self.view addSubview:button];
    [button setTitle:@"切换Laya" forState:UIControlStateNormal];
    button.frame = CGRectMake(200, 200, 100, 100);
    [button addTarget:self action:@selector(changeVC) forControlEvents:UIControlEventTouchUpInside];
}


-(void)changeVC
{
    [[AppDelegate shareDelegate]changeRootVC];
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
