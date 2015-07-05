//
//  ALViewController.m
//  ALMediaLibrary
//
//  Created by Andrea Mario Lufino on 06/29/2015.
//  Copyright (c) 2014 Andrea Mario Lufino. All rights reserved.
//

#import "ALViewController.h"
#import <ALMediaLibrary/ALMediaLibrary.h>
#import <MBProgressHUD/MBProgressHUD.h>

@interface ALViewController ()

@property (nonatomic, strong) AVPlayer *player;

@end

@implementation ALViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    
    /*! Add the hud for the loading */
    MBProgressHUD *progressHUDImage = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    
    /*! Fetch photos from library */
    [[ALMediaManager sharedManager] allPhotos:^(NSArray *assets, NSError *error) {
        
        [progressHUDImage hide:YES];
        
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.labelText = @"Loading...";
        hud.mode = MBProgressHUDModeAnnularDeterminate;
        
        /*! Get a casual asset */
        ALMediaAsset *asset = assets[4555];
        
        /*! Create the image options and customize it */
        ALImageRequestOptions *imageOptions = [ALImageRequestOptions bestQualityOptions];
        
        imageOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            hud.progress = progress;
        };
        
        /*! Retrieve the image from asset */
        [[ALMediaManager sharedManager] imageForAsset:asset
                                                 size:ALPhotoSizeMaximum
                                          contentMode:ALImageContentModeDefault
                                              options:imageOptions
                                      completionBlock:^(UIImage *image, NSDictionary *info) {
                                          [hud hide:YES];
                                          NSLog(@"Image ready!");
                                          NSLog(@"Image info :\n%@", info);
                                          self.imageView.image = image;
                                      }];
    }];
    
    MBProgressHUD *progressHUDVideo = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    
    /*! Fetch videos from library */
    [[ALMediaManager sharedManager] allVideos:^(NSArray *assets, NSError *error) {
        
        [progressHUDVideo hide:YES];
        
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.labelText = @"Loading...";
        hud.mode = MBProgressHUDModeAnnularDeterminate;
        
        /*! Get a casual asset */
        ALMediaAsset *asset = assets[144];
        
        /*! Create options to request a video and customize it */
        ALVideoRequestOptions *videoOptions = [ALVideoRequestOptions bestQualityOptions];
        
        videoOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            hud.progress = progress;
        };
        
        /*! Retrieve the AVPlayerItem from asset */
        [[ALMediaManager sharedManager] playerItemForAsset:asset
                                                   options:videoOptions
                                           completionBlock:^(AVPlayerItem *playerItem, NSDictionary *info) {
                                               hud.labelText = @"Loaded!";
                                               [hud hide:YES];
                                               NSLog(@"Video ready!");
                                               NSLog(@"Video info : \n%@", info);
                                               self.player = [AVPlayer playerWithPlayerItem:playerItem];
                                               [self.playerView.layer addSublayer:[self playerLayerWithAVPlayer:self.player]];
                                               
                                               [self.player play];
                                           }];
    }];
    
    
    
    [[ALMediaManager sharedManager] photos];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (AVPlayerLayer *)playerLayerWithAVPlayer:(AVPlayer *)player {
    AVPlayerLayer *layer = [AVPlayerLayer playerLayerWithPlayer:self.player];
    layer.frame = self.playerView.bounds;
    layer.backgroundColor = [UIColor greenColor].CGColor;
    layer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    return layer;
}

@end
