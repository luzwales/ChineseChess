//
//  Luna.h
//  ChineseChess
//
//  Created by 李夙璃 on 2017/10/22.
//  Copyright © 2017年 StarLab. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "LunaRecord.h"

// MARK: - LunaBoardState, this enum reveals the state of game, it can be over or red player's turn or black player's turn.
typedef NS_ENUM(uint8_t, LunaBoardState) {
	LunaBoardStateTurnRedSide = 0,
	LunaBoardStateTurnBlackSide = 1 << 0,
	LunaBoardStateDrawSamePositionMultiTimes = 1 << 1,
	LunaBoardStateDraw50RoundHaveNoneEat = 1 << 2,
	LunaBoardStateDrawBothSideHaveNoneAttckChess = 1 << 3,
	LunaBoardStateWinNormalRed = 1 << 4,
	LunaBoardStateWinNormalBlack = 1 << 5,
	LunaBoardStateWinLongCatchRed = 1 << 6,
	LunaBoardStateWinLongCatchBlack = 1 << 7
};

// MARK: - LunaMoveState, this enum reveals the state of a move, it can be check or mate...
typedef NS_ENUM(uint8_t, LunaMoveState) {
	LunaMoveStateSelect,
	LunaMoveStateNormal,
	LunaMoveStateEat,
	LunaMoveStateCheck,
	LunaMoveStateCheckMate,
	LunaMoveStateEatCheck,
	LunaMoveStateEatCheckMate
};

// MARK: - Typedef
typedef uint8_t Luna_Location;

typedef uint8_t Luna_Chess;

typedef uint16_t Luna_Move;

// MARK: - AI Luna.
@interface Luna : NSObject

// chess array
@property (nonnull, nonatomic, readonly) NSArray<NSNumber *> *chesses;

// the state reveals the state of game.
@property (nonatomic, readonly) LunaBoardState state;

// AI Control, the isThinking reveals the AI is thinking or not, you can stop it by setting it 'NO'.
@property (nonatomic, readwrite) BOOL isThinking;

@end

// MARK: - AI Luna. (Game)
@interface Luna (Game)

// last reocrd.
@property (nullable, nonatomic, readonly) LunaRecord *lastMove;

// see if user want to choose another chess.
- (BOOL)isAnotherChoiceWithLocation:(Luna_Location)location;

// generate legal moves.
- (nonnull NSArray<NSNumber *> *)legalMovesWithLocation:(Luna_Location)location;

// do a chess move, return a state indicates how this move affect the game.
- (LunaMoveState)moveChessWithMove:(Luna_Move)move;

// undo a chess move from move stack, move = 0 indicates there's no more move in stack.
- (Luna_Chess)regretWithMove:(nonnull Luna_Move *)move;

@end

// MARK: - AI Luna. (History)
@interface Luna (History)

// all records
@property (nonnull, nonatomic, readonly) NSArray<LunaRecord *> *records;

// count of records
@property (nonatomic, readonly) NSUInteger count;

// the record at index of records
- (nonnull LunaRecord *)recordAtIndex:(NSUInteger)idx;

// character history
@property (nonnull, nonatomic, readonly) NSString *characters;

// reset board with file record.
- (void)initBoardWithFile:(nullable NSString *)file;

// return the file record of game.
- (nonnull NSString *)historyFile;

@end
