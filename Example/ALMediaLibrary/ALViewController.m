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

@interface ALViewController () <ALMediaManagerDelegate>

@property (nonatomic, strong) AVPlayer *player;

@end

@implementation ALViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    // Add the hud for the loading
    MBProgressHUD *progressHUDImage = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    
    // Set delegate of ALMediaManager
    [[ALMediaManager sharedManager] setDelegate:self];
    
    // Use notification center
    [[ALMediaManager sharedManager] setUseNSNotificationCenter:YES];
    
    // Set observer
    [[NSNotificationCenter defaultCenter] addObserverForName:ALMediaManagerFetchMediaFinished
                                                      object:nil
                                                       queue:nil
                                                  usingBlock:^(NSNotification *note) {
                                                      NSArray *array = note.userInfo[ALMediaManagerNotificationUserInfoAssetsKey];
                                                      NSLog(@"Number of assets from notification : %@", @(array.count));
                                                  }];
    
    // Fetch photos from library
    [[ALMediaManager sharedManager] allPhotosWithOptions:[ALFetchOptions fetchOptionsOnlyLocation] callbackBlock:^(NSArray *assets, NSError *error) {
        
        [progressHUDImage hide:YES];
        
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.labelText = @"Loading...";
        hud.mode = MBProgressHUDModeAnnularDeterminate;
        
        // Get casual index to get casual asset
        int index = arc4random_uniform((int)assets.count);
        
        // Get a casual asset  
        ALMediaAsset *asset = assets[index];
        
        // Create the image options and customize it  
        ALImageRequestOptions *imageOptions = [ALImageRequestOptions bestQualityOptions];
        
        // Create the progress handler for the image download
        imageOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            hud.progress = progress;
        };
        
        // Retrieve the image from asset  
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
    
    
    // Decomment this to try to get the videos from your library
    /*
    MBProgressHUD *progressHUDVideo = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
    
    // Fetch videos from library  
    [[ALMediaManager sharedManager] allVideosWithOptions:nil callbackBlock:^(NSArray *assets, NSError *error) {
        
        [progressHUDVideo hide:YES];
        
        MBProgressHUD *hud = [MBProgressHUD showHUDAddedTo:self.view animated:YES];
        hud.labelText = @"Loading...";
        hud.mode = MBProgressHUDModeAnnularDeterminate;
        
        // Get casual index to get casual asset
        int index = arc4random_uniform((int)assets.count);
        
        // Get a casual asset  
        ALMediaAsset *asset = assets[index];
        
        // Create options to request a video and customize it  
        ALVideoRequestOptions *videoOptions = [ALVideoRequestOptions bestQualityOptions];
        
        videoOptions.progressHandler = ^(double progress, NSError *error, BOOL *stop, NSDictionary *info) {
            hud.progress = progress;
        };
        
        // Retrieve the AVPlayerItem from asset  
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
     */
    
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Player item layer

- (AVPlayerLayer *)playerLayerWithAVPlayer:(AVPlayer *)player {
    AVPlayerLayer *layer = [AVPlayerLayer playerLayerWithPlayer:self.player];
    layer.frame = self.playerView.bounds;
    layer.backgroundColor = [UIColor greenColor].CGColor;
    layer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    
    return layer;
}

#pragma mark - ALMediaManager delegate

- (void)didFinishFetchMedia:(NSArray *)assets ofType:(ALMediaAssetType)type {
    NSLog(@"I'm the delegate! Your assets are %@", @(assets.count));
}

- (void)didFinishRetrieveImageAsset:(UIImage *)image {
    NSLog(@"I'm the delegate! Your image has been retrieved!");
}

- (void)didFinishRetrieveVideoAsset:(AVPlayerItem *)playerItem {
    NSLog(@"I'm the delegate! You player item has been retrieved!");
}

@end
