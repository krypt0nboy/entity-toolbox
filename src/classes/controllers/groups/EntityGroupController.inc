<?php

/**
 * Class EntityGroupController
 */
class EntityGroupController {

  use EntityToolboxCommonTraits;
  /**
   * @var string $groupName
   *   The group name for this entity group controller.
   */
  protected $name;
  /**
   * @var array $groupInfo
   *   The group type info.
   */
  protected $info;

  /**
   * EntityGroup constructor.
   *
   * @param string $name
   *   The group's name.
   */
  public function __construct($name) {
    $this->name = $name;
    $this->info = entity_toolbox_entity_group_get_info($this->name);
  }

  /**
   * @return string
   */
  public function getName() {
    return $this->name;
  }

  /**
   * @param string $name
   */
  public function setName($name) {
    $this->name = $name;
  }

  /**
   * @return array
   */
  public function getInfo() {
    return $this->info;
  }

  /**
   * @param array $info
   */
  public function setInfo($info) {
    $this->info = $info;
  }

  /**
   * Returns an group instance.
   *
   * @return EntityGroup
   */
  public function getInstance() {
    $class    = $this->info['classes']['group'];
    $instance = new $class($this->name);

    return $instance;
  }

  /**
   * Extracts the fieldable entity types of an entity group.
   *
   * @param EntityGroup $group
   *   The entity group.
   *
   * @return string[]
   */
  public function extractFieldableEntityTypes($group) {
    $entityTypes = array();
    foreach ($group->getEntityTypes() as $entityType) {
      $toolboxInfo = entity_toolbox_get_info($entityType);
      if ($toolboxInfo['fieldable']) {
        $entityTypes[] = $entityType;
      }
    }

    return $entityTypes;
  }

  /**
   * Extracts the non fieldable entity types of an entity group.
   *
   * @param EntityGroup $group
   *   The entity group.
   *
   * @return string[]
   */
  public function extractNonFieldableEntityTypes($group) {
    $entityTypes = array();
    foreach ($group->getEntityTypes() as $entityType) {
      $toolboxInfo = entity_toolbox_get_info($entityType);
      if (!$toolboxInfo['fieldable']) {
        $entityTypes[] = $entityType;
      }
    }

    return $entityTypes;
  }

  /**
   * Loads the group's entities.
   *
   * @param EntityGroup $group
   *   The entity group.
   * @param array       $conditions
   *   The conditions to load the entities.
   *
   * @return EntityToolbox[]
   */
  public function loadEntities($group, array $conditions = array()) {
    $loaded = array();
    foreach ($group->getEntityTypes() as $entityType) {
      $loaded[$entityType] = entity_load($entityType, FALSE, $conditions);
    }
    $group->setEntities($loaded);

    return $loaded;
  }

  /**
   * Builds the group's hierarchy based on their properties and weight.
   *
   * @param EntityGroup $group
   *   The entity group.
   *
   * @return array
   */
  public function buildHierarchy($group) {
    //@todo add cache for hierarchy
    $hierarchy   = array();
    $parentTypes = array();
    foreach ($group->getFieldableEntityTypes() as $entityType) {
      $parentTypes[$entityType] = entity_type_get_parents($entityType);
    }

    return $hierarchy;
  }

  /**
   * Builds the group's tree.
   *
   * @param EntityGroup $group
   *   The entity group.
   *
   * @return array
   */
  public function buildTree($group) {

  }

}