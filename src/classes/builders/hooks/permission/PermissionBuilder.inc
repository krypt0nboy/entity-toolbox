<?php

/**
 * Class PermissionBuilder
 */
class PermissionBuilder extends HookBuilder {
  use ModuleDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(
      array(
        'hook' => 'permission',
      ),
      $args
    );
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->buildEntitiesPermissions();
    $this->unsetKeysEval();

    return $this->build;
  }

  /**
   * @param null|string $entityType
   * @return array
   */
  public function buildEntitiesPermissions($entityType = NULL) {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    if (isset($entityType)) {
      $structure[$entityType]          = array(
        'type'   => 'array',
        'method' => 'buildEntityPermissions'
      );
      $keyBuildersClasses[$entityType] = 'PermissionEntityPermissionsBuilder';
    }
    else {
      foreach ($this->getModuleEntities() as $moduleEntity) {
        $structure[$moduleEntity]          = array(
          'type'   => 'array',
          'method' => 'buildEntityPermissions'
        );
        $keyBuildersClasses[$moduleEntity] = 'PermissionEntityPermissionsBuilder';
      }
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuildersClasses);
    foreach ($keyBuildersClasses as $moduleEntity => $keyBuildersClass) {
      $toolboxInfo                    = entity_toolbox_get_info($moduleEntity);
      $keyBuildersArgs[$moduleEntity] = array(
        'entity_type' => $moduleEntity,
        'fieldable'   => $toolboxInfo['fieldable']
      );
    }
    foreach ($keyBuildersArgs as $moduleEntity => $buildersArgs) {
      $this->setKeyBuilder($moduleEntity, $this->keyBuilderGetInstance($keyBuildersClasses[$moduleEntity], $buildersArgs));
    }
    foreach ($this->moduleEntities as $moduleEntity) {
      $this->build[$moduleEntity] = $this->getKeyBuilder($moduleEntity)
                                         ->build();
    }

    return $this->build;
  }

  /**
   * @param null|string $entityGroup
   * @return array
   */
  public function buildEntityGroupPermissions($entityGroup = NULL) {

  }
}