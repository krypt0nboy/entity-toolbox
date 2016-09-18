<?php

/**
 * Class PermissionEntityPermissionsBuilder
 */
class PermissionEntityPermissionsBuilder extends PermissionKeyBuilder {
  use EntityDependentTraits, EntityDependentBuilderTraits, EntityToolboxDependentTraits, EntityToolboxDependentBuilderTraits;

  /** {{@inheritdoc}} */
  public function build() {
    $this->prepareStructure();
    foreach (array_keys($this->getStructure()) as $operation) {
      $this->setKeyBuild($operation, $this->buildEntityPermission($operation));
    }
    $this->unsetKeysEval();

    return $this->build;
  }

  protected function initTemplateVars() {
    $flattened = $this->extractToolboxInfoTemplateVars();
    $this->templateVars += $flattened;
  }

  /** {{@inheritdoc}} */
  protected function prepareStructure() {
    $structure          = array();
    $keyBuildersClasses = array();
    $keyBuildersArgs    = array();
    foreach ($this->toolboxInfo['operations'] as $operation => $operationInfo) {
      $permissionName                      = $operation . $this->processValueTemplate(' any %toolbox_info_entity_type%');
      $structure[$permissionName]          = array(
        'type'   => 'array',
        'method' => 'buildEntityPermission',
      );
      $keyBuildersClasses[$permissionName] = 'PermissionEntityOperationPermissionBuilder';
      $keyBuildersArgs[$permissionName]    = array(
        'entity_type'    => $this->entityType,
        'operation_name' => $operation,
        'operation_info' => $operationInfo,
      );
      if ($this->fieldable) {
        $function                            = $this->processValueTemplate('%toolbox_info_entity_type%_get_types');
        foreach ($function() as $type) {
          echo '';
        }
      }
    }
    $this->__set('structure', $structure);
    $this->setKeyBuildersClasses($keyBuildersClasses);
    foreach ($keyBuildersArgs as $operation => $buildersArgs) {
      $this->setKeyBuilder($operation, $this->keyBuilderGetInstance($keyBuildersClasses[$operation], $buildersArgs));
    }
  }

  /**
   * @param $operation
   * @return mixed
   */
  protected function buildEntityPermission($operation) {
    return $this->getKeyBuilder($operation)->build();
  }
}