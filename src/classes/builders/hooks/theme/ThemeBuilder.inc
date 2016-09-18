<?php

/**
 * Class ThemeBuilder
 */
class ThemeBuilder extends HookBuilder {
  use ModuleDependentTraits;

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook' => 'theme',
    ), $args);
    parent::__construct($args);
  }

  /** {{@inheritdoc}} */
  public function build() {
    $this->buildEntityThemes();
    $this->unsetKeysEval();

    return $this->build;
  }

  /**
   * Builds the module's entity themes.
   *
   * @param null|string $entityType
   *   The entity type.
   *
   * @return array
   */
  public function buildEntityThemes($entityType = NULL) {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    if (isset($entityType)) {
      $structure[$entityType]          = array(
        'type'   => 'array',
        'method' => 'buildEntityTheme'
      );
      $keyBuildersClasses[$entityType] = 'EntityThemeBuilder';
    }
    else {
      foreach ($this->getModuleEntities() as $moduleEntity) {
        $structure[$moduleEntity]          = array(
          'type'   => 'array',
          'method' => 'buildEntityTheme'
        );
        $keyBuildersClasses[$moduleEntity] = 'EntityThemeBuilder';
      }
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuildersClasses);
    foreach ($keyBuildersClasses as $moduleEntity => $keyBuildersClass) {
      $keyBuildersArgs[$moduleEntity] = array(
        'entity_type' => $moduleEntity,
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

  /** {{@inheritdoc}} */
  protected function keyBuilderGetInstance($keyBuilderClass, array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'module' => $this->constructArgs['module']
    ), $args);

    return parent::keyBuilderGetInstance($keyBuilderClass, $args);
  }
}