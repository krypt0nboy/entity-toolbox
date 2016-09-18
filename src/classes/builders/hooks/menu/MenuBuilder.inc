<?php

/**
 * Class MenuBuilder
 */
class MenuBuilder extends HookBuilder {

  use ModuleDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'menu',
    ), $args);
    parent::__construct($args);
  }

//  /**
//   * Main build function.
//   *
//   * @param string $buildKey
//   *   The build lowercase method.
//   * @param string|null $buildArg
//   *   The build arg.
//   *
//   * @return array
//   */
//  public function build($buildKey, $buildArg = NULL) {
//    if (isset($buildKey)) {
//      $cKey   = lowercase2camelcase($buildKey);
//      $method = 'build' . $cKey;
//      if (method_exists($this, $method)) {
//        $build = $this->$method($buildArg);
//        $this->unsetKeysEval();
//
//        return $build;
//      }
//    }
//    else {
//      $this->buildEntityGroupMenus();
//      $this->unsetKeysEval();
//
//      return $this->build;
//    }
//  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->buildEntityGroupMenus();
    $this->unsetKeysEval();

    return $this->build;
  }

  /**
   * Builds the module's entity group menus.
   *
   * @param null|string $entityGroup
   *   The entity group.
   *
   * @return array
   */
  public function buildEntityGroupMenus($entityGroup = NULL) {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    if (isset($entityGroup)) {
      $structure[$entityGroup]          = array(
        'type'   => 'array',
        'method' => 'buildEntityGroupMenuItems'
      );
      $keyBuildersClasses[$entityGroup] = 'EntityGroupMenuItemsBuilder';
    }
    else {
      foreach ($this->moduleInfo->entity_groups as $group) {
        $structure[$group]          = array(
          'type'   => 'array',
          'method' => 'buildEntityGroupMenus'
        );
        $keyBuildersClasses[$group] = 'EntityGroupMenuItemsBuilder';
      }
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuildersClasses);
    foreach ($keyBuildersClasses as $group => $keyBuildersClass) {
      $keyBuildersArgs[$group] = array(
        'entity_group' => $group,
      );
    }
    foreach ($keyBuildersArgs as $group => $buildersArgs) {
      $this->setKeyBuilder($group, $this->keyBuilderGetInstance($keyBuildersClasses[$group], $buildersArgs));
    }
    foreach ($this->moduleInfo->entity_groups as $group) {
      $this->build[$group] = $this->getKeyBuilder($group)
                                  ->build();
    }

    return $this->build;
  }
}