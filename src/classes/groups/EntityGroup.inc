<?php

/**
 * @file
 *
 * This file contains Entity group classes.
 */

/**
 * Class EntityGroup
 */
class EntityGroup {

  /**
   * @var string $groupType
   *   The group type.
   */
  protected $groupType;

  /**
   * @var array $groupInfo
   *   The group info.
   */
  protected $groupInfo;

  /**
   * @var \EntityToolbox[] $tree
   *   An array of entities, forming a tree.
   */
  protected $tree;

  /**
   * EntityGroup constructor.
   *
   * @param $group_type
   *   The group type.
   */
  public function __construct($group_type) {
    $this->groupType = $group_type;
    $this->groupInfo = entity_toolbox_entity_group_get_info($group_type);
  }

  /**
   * Returns the group name.
   *
   * @return string
   */
  public function groupType() {
    return $this->groupType;
  }

  /**
   * Returns the group info.
   *
   * @return array
   */
  public function groupInfo() {
    return $this->groupInfo;
  }

  /**
   * Returns the entity types attached to that group.
   *
   * @return mixed
   */
  public function groupEntities() {
    return $this->groupInfo['entities'];
  }
}